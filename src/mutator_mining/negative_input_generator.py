import os
from openai import OpenAI
import re
from pathlib import Path
import logging
import json
import anthropic
import time

logger = logging.getLogger(__name__)

# Setup OpenAI client
openai_client = OpenAI(
    api_key=os.environ.get("OPENAI_API_KEY"),  # This is the default and can be omitted
)

# Setup Anthropic client
anthropic_client = anthropic.Anthropic(
    api_key=os.environ.get("ANTHROPIC_API_KEY")
)

llm_vendor = "openai"

model = "o1-mini"
# model = "claude-3-5-sonnet-20241022"

bug_report_directory = "llvm_bug_report"
out_folder = "llvm_fixed_code"

# Helper Functions
def setup_logger():
    logging.basicConfig(filename="fixed_code_generator.log", level=logging.INFO)
    logger.info(f"Logging started for fixed code generation!")

def openai_api_request(conversation):
    # Call the OpenAI API
    chat_completion = openai_client.chat.completions.create(
        messages=conversation,
        model=model,
    )

    # Write the response
    response = chat_completion.choices[0].message.content

    return response

def anthropic_api_request(conversation, retries=3, delay=60):
    for attempt in range(retries):
        try:
            message = anthropic_client.messages.create(
                model=model,
                max_tokens=8192,
                messages=conversation,
                timeout=120
            )
            
            # Return the response
            return message.content[0].text
        except Exception as e:
            logger.error(f"Attempt {attempt + 1} failed: {e}")
            if attempt < retries - 1:
                logger.info(f"Retrying in {delay} seconds...")
                time.sleep(delay)
            else:
                logger.error("All retries failed. Please check the server status or your request.")
                return None  # or raise an appropriate exception

def llm_api_request(conversation):
    if llm_vendor == "openai":
        response = openai_api_request(conversation)
    elif llm_vendor == "anthropic":
        response = anthropic_api_request(conversation)
    return response

def remove_c_comments(code):
    """
    Removes all comments from C code.
    
    :param code: A string containing C code.
    :return: A string with comments removed.
    """
    # Regular expression patterns
    single_line_comment = r'//.*'  # Match single-line comments
    multi_line_comment = r'/\*.*?\*/'  # Match multi-line comments (non-greedy)

    # Remove multi-line comments
    code_without_multi_line = re.sub(multi_line_comment, '', code, flags=re.DOTALL)

    # Remove single-line comments
    code_without_comments = re.sub(single_line_comment, '', code_without_multi_line)

    return code_without_comments

def list_ids_from_c_files(directory):
    """
    Lists the IDs of C files in a directory.
    
    :param directory: The directory to search for C files.
    :return: A list of IDs.
    """
    c_files = Path(directory).rglob("*.c")  # Get all .c files
    ids = [file.stem for file in c_files]  # Use `stem` to get the filename without the extension
    return ids

def number_of_processed_bug_reports(directory):
    history_files = Path(directory).glob("*.json")
    return len(list(history_files))

def write_fixed_code(code, bug_id):
    """
    Write the fixed code to a file.
    
    :param code: The fixed code to write.
    :param bug_id: The ID of the bug.
    :return: None
    """
    if code:
        output_file = f"{out_folder}/{bug_id}-fixed.c"
        with open(output_file, "w", encoding="utf-8") as file:
            file.write(code)
        logger.info(f"Fixed code saved to {output_file}")

def save_conversation(bug_id, messages):
    """
    Save the conversation to a json file.
    
    :param bug_id: The ID of the bug.
    :param conversation: The conversation to save.
    :return: None
    """
    conversation = {
        "messages": [
            {
                "role": message.role,
                "content": message.content
            } if hasattr(message, 'role') and hasattr(message, 'content') else message
            for message in messages
        ]
    }
    # print(conversation)

    with open(f"{out_folder}/{bug_id}-history.json", "w", encoding="utf-8") as json_file:
        json.dump(conversation, json_file, indent=4)
    logger.info(f"Conversation saved to {bug_id}-history.json")


def main():
    setup_logger()

    bug_ids = list_ids_from_c_files(bug_report_directory)

    processed_ids = [id.replace("-fixed", "") for id in list_ids_from_c_files(out_folder)]

    for bug_id in bug_ids:

        if number_of_processed_bug_reports(out_folder) >= 250:
            logger.info("Number of processed bug reports reached 250. Exiting.")
            break
        
        if bug_id in processed_ids:
            continue
        
        try: 
            with open(f"{bug_report_directory}/{bug_id}.txt", 'r') as file:
                bug_report_content = file.read()
            with open(f"{bug_report_directory}/{bug_id}.c", 'r') as file:
                code = remove_c_comments(file.read())
        except:
            continue
        
        logger.info(f"Fixed code generation started for {bug_id}")
        prompt = f"You are an experienced C expert. Your task is to read the following bug report and identify what makes the LLVM buggy. Then, mutate the following C program to fix the issue without mutating the comments in the code or adding new comments.\nThe response should include only the description of the mutation and the mutated C code.\n###Bug Report:\n{bug_report_content}\nOriginal C Code:\n```c\n{code}\n```"
        # logger.info(prompt)

        messages = [
            # {   "role": "system", "content": "You are an experienced C expert." },
            {
                "role": "user",
                "content": prompt
            }
        ]

        response = llm_api_request(messages)
        if response is None:
            continue

        # Regex pattern to extract the content inside ```c and ```
        code_block = re.search(r"```c(.*?)```", response, re.DOTALL)
        # Extracting and printing the code
        extracted_code = code_block.group(1).strip() if code_block else None

        # TODO: check if the code is mutated
        # TODO: refine the code
        write_fixed_code(extracted_code, bug_id)
        messages.append(
            {
                "role": "assistant",
                "content": response
            }
        )
        save_conversation(bug_id, messages)
        
if __name__ == "__main__":
    main()
#TODO: send godbolt api to validate the mutation
#TODO: agentize