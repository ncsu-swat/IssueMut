import requests
import json
from datetime import datetime, date, timezone
from dateutil.parser import isoparse
import time
import logging
import argparse
import os

logger = logging.getLogger(__name__)

# Define GitHub repository details
owner = "llvm"
repo = "llvm-project"

# GitHub API URL
base_url = f"https://api.github.com/repos/{owner}/{repo}/issues"

# GitHub token (for rate limiting, optional)
# token = "your_personal_access_token"  # If you have one, otherwise you can skip authentication
token = ""

headers = {
    "Accept": "application/vnd.github.v3+json",
}
if token:
    headers["Authorization"] = f"token {token}"

def setup_logger():
    logging.basicConfig(filename="llvm_bug_report_extractor.log", level=logging.INFO)
    logger.info(f"Logging started for LLVM bug report extraction!")

def github_api_call(url):
    headers = {
        "Accept": "application/vnd.github.v3+json",
    }
    if token:
        headers["Authorization"] = f"token {token}"

    # Send request to GitHub API
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        return response.json()
    else:
        logger.error(f"Failed to retrieve {url}: {response.status_code}")
        return None

# Function to get an issue by its ID
def get_issue_by_id(issue_id):
    issue_url = f"{base_url}/{issue_id}"
    return github_api_call(issue_url)

# Function to extract the discussion from an issue
def extract_discussion(issue):
    if issue:
        discussion = []
        # Issue body
        discussion.append(f"Issue Title: {issue['title']}")
        discussion.append(f"Original Post: {issue['body']}\n")

        # Get comments if they exist
        if issue['comments'] > 0:
            comments_response = github_api_call(issue['comments_url'])
            # print(comments_response)
            for comment in comments_response:
                try:
                    discussion.append(f"Comment by {comment['user']['login']}: {comment['body']}")
                except (TypeError, KeyError):
                    logger.error(f"Skipping invalid comment: {comment}")  # Avoid crashing
        
        return "\n".join(discussion)
    return "No discussion found."

def extract_testcase(issue, out_folder: str):
    if not issue:
        return None
    
    events_response = github_api_call(issue['events_url'])

    if not events_response:
        return None
    
    for event in events_response:
        if event['event'] == 'referenced' and event['commit_url'] is not None:
            logger.info(f"Processing commit: {event['commit_url']}")

            commit_reponse = github_api_call(event['commit_url'])
            if not commit_reponse:
                continue
            
            for file in commit_reponse['files']:
                if (file['filename'].endswith('.c') or file['filename'].endswith('.C')) and "test" in file['filename']:
                    # while True:
                    contents_response = github_api_call(file['contents_url'])
                    testcase_response = requests.get(contents_response['download_url'])
                    if testcase_response.status_code == 200:
                        with open(f"{out_folder}/{issue['number']}.c", "w") as f:
                            f.write(testcase_response.text)
                            return True
                    else:
                        logger.error(f"Failed to download {file['filename']}: {testcase_response.status_code}")
    
    return False


def is_within_date_range(timestamp: str, start_date: datetime, end_date: datetime):

    # Convert to datetime object
    dt = isoparse(timestamp)  # Parses ISO format

    # Check if the timestamp is within range
    return start_date <= dt <= end_date

def after_end_date(timestamp, end_date: datetime):
    # Convert to datetime object
    dt = isoparse(timestamp)  # Parses ISO format
    return dt > end_date

def date_bounds_utc(start_d: date, end_d: date):
    start_dt = datetime(start_d.year, start_d.month, start_d.day, 0, 0, 0, tzinfo=timezone.utc)
    end_dt = datetime(end_d.year, end_d.month, end_d.day, 23, 59, 59, tzinfo=timezone.utc)
    return start_dt, end_dt

def collect_llvm_bug_reports(out_folder: str, start_d: date, end_d: date):
    start_dt, end_dt = date_bounds_utc(start_d, end_d)
    os.makedirs(out_folder, exist_ok=True)

    page_number = 1
    since_iso = f"{start_d.isoformat()}T00:00:00Z"

    while True:
        issue_url = f"{base_url}?state=closed&per_page=100&page={page_number}&since={since_iso}&direction=asc"

        issues = github_api_call(issue_url)
        for issue in issues:
            
            if "pull_request" in issue:
                continue

            if issue["state_reason"] != "completed":
                logger.info(f"Skipping issue {issue['number']} because it is not completed")
                continue
            
            created_at = issue.get("created_at")
            closed_at = issue.get("closed_at")
            if not created_at or not closed_at:
                continue
            
            if (not is_within_date_range(created_at, start_dt, end_dt) or
                not is_within_date_range(closed_at, start_dt, end_dt)):
                logger.info(f"Skipping issue {issue['number']} because it is not within the date range")
                continue
            
            logger.info(f"========= Processing issue {issue['number']} =========")

            if not extract_testcase(issue, out_folder):
                logger.info(f"Skipping issue {issue['number']} because it has no testcase")
                continue
            
            # Save bug report
            with open(f"{out_folder}/{issue['number']}.txt", "w") as f:
                discussion = extract_discussion(issue)
                f.write(discussion)
            
            
        last_created = issues[-1].get("created_at")
        if last_created and after_end_date(last_created, end_dt):
            break

        page_number += 1

def parse_args():
    p = argparse.ArgumentParser()
    p.add_argument("--out_folder", default="llvm_bug_report")
    p.add_argument("--start_date", default="2023-01-01")
    p.add_argument("--end_date", default="2024-10-31")
    return p.parse_args()

def parse_ymd(s):
    y, m, d = s.split("-")
    return date(int(y), int(m), int(d))

# Main logic to collect LLVM bug reports
def main():
    args = parse_args()
    out_folder = args.out_folder
    start_date = parse_ymd(args.start_date)
    end_date = parse_ymd(args.end_date)

    setup_logger()
    print("Start extracting LLVM bug reports... (please check log file)")
    collect_llvm_bug_reports(out_folder, start_date, end_date)
    logger.info(f"Finished processing bug reports for LLVM!")

if __name__ == "__main__":
    main()
