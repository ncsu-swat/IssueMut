import requests
from bs4 import BeautifulSoup
import logging
from datetime import datetime, date
import argparse
import os

logger = logging.getLogger(__name__)

# Constants
BASE_URL = "https://gcc.gnu.org/bugzilla/"
GCC_REPO_URL = "https://github.com/gcc-mirror/gcc/raw/"
DATE_FORMAT = "%Y-%m-%d"

# Helper Functions
def setup_logger():
    logging.basicConfig(filename="gcc_bug_report_extractor.log", level=logging.INFO)
    logger.info(f"Logging started for GCC bug report extraction!")

def parse_date(date_string):
    return datetime.strptime(date_string, DATE_FORMAT).date()

def fetch_page(url):
    response = requests.get(url)
    response.raise_for_status()
    return BeautifulSoup(response.text, 'html.parser')

# Extractors
def extract_bug_ids(soup):
    return [td.contents[1].text for td in soup.find_all("td", {"class": "first-child bz_id_column"})]

def extract_bug_report_details(bug_report_soup):
    """
    Extract title and reported date from a bug report page.
    """
    title = bug_report_soup.find("span", {"id": "short_desc_nonedit_display"}).contents[0]
    reported_date_string = bug_report_soup.find("th", string="\n      Reported:\n    ").parent.find("td").contents[0].split(" ")[0]
    return title, reported_date_string

def extract_commit_links(bug_report_soup):
    commits = []
    for commit_span in bug_report_soup.find_all("span", string="GCC Commits"):
        comment = commit_span.parent.parent.parent.parent
        if is_master_branch(comment):
            commit = comment.find("a", href=lambda href: href and "gitweb.cgi?p=gcc.git;h=" in href)
            if commit:
                commits.append(commit['href'])
    return commits

def extract_testcase_links(commit_soup, sha):
    """
    Extract testcases from a commit page.
    """
    testcases = []
    for diff_tree in commit_soup.find_all("table", {"class": "diff_tree"}):
        links = diff_tree.find_all('a', string=lambda text: text and "testsuite" in text)
        testcases.extend([(sha, link.string) for link in links])
    return testcases

def extract_one_testcase_link(commit_soup, sha):
    """
    Extract one testcase from a commit page.
    """
    testcases = []
    for diff_tree in commit_soup.find_all("table", {"class": "diff_tree"}):
        links = diff_tree.find_all('a', string=lambda text: text and "testsuite" in text)
        testcases.extend([(sha, link.string) for link in links])
    return testcases[0] if testcases != [] else None

# Extract bug details with error handling
def safe_find_text(soup_element, tag, **kwargs):
    element = soup_element.find(tag, **kwargs)
    return element.get_text(strip=True) if element else "N/A"

# Validators
def is_c_plus_plus(bug_report_soup):
    component = bug_report_soup.find("a", string="Component:").parent.parent.find("td").contents[0]
    return "c++" in component

def before_starting_date(start_date, reported_date_string):
    return parse_date(reported_date_string) < start_date

def is_master_branch(comment):
    comment_text = comment.find("pre", {"class": "bz_comment_text"})
    return "trunk branch has been updated" in comment_text.text or "master branch has been updated" in comment_text.text

# Core Logic
def process_testcases(out_folder, bug_id, sha, testcases):
    """
    Process testcases and save them to files.
    """
    for idx, (sha, testcase_path) in enumerate(testcases, start=1):
        if not testcase_path.endswith((".c", ".C")):
            continue
        try:
            response = requests.get(f"{GCC_REPO_URL}{sha}/{testcase_path}")
            response.raise_for_status()
            with open(f"{out_folder}/{bug_id}-{idx}.c", "w") as file:
                file.write(response.text)
        except Exception as e:
            logger.warning(f"Failed to fetch {testcase_path} for Bug ID {bug_id}: {e}")

def process_one_testcase(out_folder, bug_id, sha, testcase):
    """
    Process one testcase and save it to a file.
    """
    if testcase is None:
        return False
    
    sha, testcase_path = testcase
    if not testcase_path.endswith((".c", ".C")):
        return False
    try:
        response = requests.get(f"{GCC_REPO_URL}{sha}/{testcase_path}")
        response.raise_for_status()
        with open(f"{out_folder}/{bug_id}.c", "w") as file:
            file.write(response.text)
        return True
    except Exception as e:
        logger.warning(f"Failed to fetch {testcase_path} for Bug ID {bug_id}: {e}")
        return False


def process_bug_report(out_folder, bug_report_id, soup):
    bug_summary = safe_find_text(soup, "span", id="subtitle")
    product = safe_find_text(soup, "td", id="field_container_product")
    component = safe_find_text(soup, "td", id="field_container_component")

    keywords = safe_find_text(soup, "td", id="field_container_keywords")
    known_to_work = safe_find_text(soup, "td", id="field_container_cf_known_to_work")
    known_to_fail = safe_find_text(soup, "td", id="field_container_cf_known_to_fail")

    # Extract comments
    comments = []
    for comment_div in soup.find_all("div", class_="bz_comment"):
        user = safe_find_text(comment_div, "span", class_="fn")
        time = safe_find_text(comment_div, "span", class_="bz_comment_time")
        text = safe_find_text(comment_div, "pre", class_="bz_comment_text")
        comments.append({"user": user, "time": time, "text": text})


    # Define the output file path
    output_file = f"{out_folder}/{bug_report_id}.txt"

    # Open the file in write mode
    with open(output_file, "w", encoding="utf-8") as file:
        # Write the bug details
        file.write(f"Bug Summary: {bug_summary}\n")
        file.write(f"Product: {product}\n")
        file.write(f"Component: {component}\n")
        file.write(f"Keywords: {keywords}\n")
        file.write(f"Known to Work: {known_to_work}\n")
        file.write(f"Known to Fail: {known_to_fail}\n")
        file.write("\nComments:\n")
        
        # Write the comments
        for comment in comments:
            file.write(f"- User: {comment['user']} | Time: {comment['time']}\n")
            file.write(f"  Text: {comment['text']}\n\n")

    logger.info(f"Bug report summary successfully written to {output_file}")

def collect_bug_report_data(start_date, end_date, out_folder):
    start_date_string = start_date.strftime(DATE_FORMAT)
    end_date_string = end_date.strftime(DATE_FORMAT)

    bug_list_url = (
        f"{BASE_URL}buglist.cgi?bug_status=RESOLVED&cf_known_to_fail_type=allwords"
        f"&cf_known_to_work_type=allwords&chfieldfrom={start_date_string}&chfieldto={end_date_string}"
        f"&limit=0&order=bug_id%20DESC&query_format=advanced&resolution=FIXED"
    )

    soup = fetch_page(bug_list_url)
    for bug_id in extract_bug_ids(soup):
        logger.info(f"Processing Bug Report: {bug_id}")
        bug_report_soup = fetch_page(f"{BASE_URL}show_bug.cgi?id={bug_id}")

        if is_c_plus_plus(bug_report_soup):
            continue

        title, reported_date_string = extract_bug_report_details(bug_report_soup)
        if before_starting_date(start_date, reported_date_string):
            break

        logger.info(f"Bug Title: {title}")

        commit_links = extract_commit_links(bug_report_soup)
        if commit_links == []:
            continue

        for commit_link in commit_links:
            sha = commit_link.split("gitweb.cgi?p=gcc.git;h=")[1]
            commit_soup = fetch_page(commit_link)
            testcase = extract_one_testcase_link(commit_soup, sha)
            testcase_exists = process_one_testcase(out_folder, bug_id, sha, testcase)
        
        if testcase_exists:
            # Bug Report Summary
            process_bug_report(out_folder, bug_id, bug_report_soup)

def parse_args():
    p = argparse.ArgumentParser()
    p.add_argument("--out_folder", default="gcc_bug_report")
    p.add_argument("--start_date", default="2023-01-01", help="YYYY-MM-DD")
    p.add_argument("--end_date",   default="2024-10-31", help="YYYY-MM-DD")
    return p.parse_args()

def parse_ymd(s: str) -> date:
    y, m, d = s.split("-")
    return date(int(y), int(m), int(d))

# Main Function
def main():
    args = parse_args()
    out_folder = args.out_folder
    start_date = parse_ymd(args.start_date)
    end_date = parse_ymd(args.end_date)

    setup_logger()
    os.makedirs(out_folder, exist_ok=True)
    print("Start extracting GCC bug reports... (please check log file)")
    collect_bug_report_data(start_date, end_date, out_folder)
    logger.info(f"Finished processing bug reports for {out_folder}!")

if __name__ == "__main__":
    main()