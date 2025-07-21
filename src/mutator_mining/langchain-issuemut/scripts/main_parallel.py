from pathlib import Path
import os
import shutil
import re
import tomllib
import random
import logging
import json
import difflib
import subprocess
from typing import TypedDict, Literal, Dict, Any, Union
import concurrent.futures
import csv
from datetime import datetime
from tqdm import tqdm

# LangChain and LangGraph imports for orchestration and state management
from langchain_google_genai import ChatGoogleGenerativeAI
from langgraph.graph import StateGraph, END
from langchain_core.messages import HumanMessage

# --- 1. CONFIGURATION AND CONSTANTS ---

DBG = 0  # Set to 1 for verbose debug output
logger = logging.getLogger(__name__)

# --- Project and Environment Setup ---
PROJECT_ROOT = Path(__file__).resolve().parents[3]
os.chdir(PROJECT_ROOT)
SCRIPT_DIR = Path(__file__).resolve().parent
config_path = SCRIPT_DIR / "config.txt"

# Setup for local 'sed' utility to ensure consistent behavior
local_sed_dir = Path(__file__).resolve().parents[1] / "bin"
sed_env = os.environ.copy()
sed_env["PATH"] = f"{str(local_sed_dir)}:{sed_env['PATH']}"
if DBG:
    print(f"Project Root: {PROJECT_ROOT}")
    print(f"Using local sed from: {local_sed_dir}")
    print("DEBUG MODE: LLM prompts and responses will be logged")

# --- Global Settings ---
MAX_REFINEMENT_ITERATIONS = 10
MAX_WORKERS = os.cpu_count() or 4  # Use all available CPU cores, default to 4

# --- 2. LLM INITIALIZATION ---

if "GOOGLE_API_KEY" not in os.environ:
    print("WARNING: GOOGLE_API_KEY not found in environment. Using hardcoded key.")
    os.environ["GOOGLE_API_KEY"] = ""

llm = ChatGoogleGenerativeAI(
    model="gemini-2.5-pro-preview-06-05",
    temperature=0.3,
    max_output_tokens=60000,
    # This flag is often recommended for better compatibility with Gemini's chat format.
    convert_system_message_to_human=True,
)

# --- 3. HELPER FUNCTIONS ---

def setup_logger():
    """Initializes logging to a file."""
    logging.basicConfig(filename=f"{SCRIPT_DIR}/mutator_generator.log", level=logging.INFO,
                        format='%(asctime)s - %(levelname)s - %(message)s')
    logger.info("--- Logging started for new mutator generation session ---")

def safe_get_content(response) -> str:
    """Safely extracts content from LLM response."""
    if hasattr(response, 'content'):
        return str(response.content)
    return str(response)

def log_llm_interaction(prompt: str, response_content: Any, node_name: str = "Unknown"):
    """Logs LLM prompts and responses when DBG is enabled."""
    if DBG == 1:
        content_str = str(response_content) if response_content is not None else "None"
        logger.info(f"=== LLM INTERACTION in {node_name} ===")
        logger.info(f"PROMPT:\n{prompt}")
        logger.info(f"RESPONSE:\n{content_str}")
        logger.info(f"=== END LLM INTERACTION ===")

def read_config_file(file_path: Path) -> dict:
    """Reads the TOML configuration file."""
    try:
        with open(file_path, "rb") as f:
            return tomllib.load(f)
    except (FileNotFoundError, tomllib.TOMLDecodeError) as e:
        logger.critical(f"FATAL: Could not read or parse config file at {file_path}. Error: {e}")
        exit(1)

def create_copy(content: str, write_path: Path):
    """Safely writes content to a file."""
    try:
        write_path.parent.mkdir(parents=True, exist_ok=True)
        write_path.write_text(content)
    except IOError as e:
        logger.error(f"Error writing to file {write_path}: {e}")

def opener(path: Path) -> str:
    """Reads content from a file."""
    return path.read_text() if path.exists() else ""

def remove_c_comments(code: str) -> str:
    """Strips C-style comments from a string."""
    code = re.sub(r'//.*', '', code)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    return code

def remove_bash_comments(code: str) -> str:
    """Strips Bash-style comments."""
    return re.sub(r'^\s*#.*$', '', code, flags=re.MULTILINE)

def run_clang_format(file_path: Path):
    """Runs clang-format in-place on a file."""
    try:
        subprocess.run(["clang-format", "-i", str(file_path)], check=True, timeout=10)
    except (subprocess.CalledProcessError, FileNotFoundError, subprocess.TimeoutExpired) as e:
        logger.warning(f"Could not format {file_path.name}: {e}")

# --- LLM Response Parsers ---

def bash_code_finder(response_content: Union[str, Any]) -> str:
    """Extracts a bash script from code blocks."""
    content = str(response_content)
    match = re.search(r"<code>(.*?)</code>", content, re.DOTALL)
    if not match:
        match = re.search(r"```(?:bash|sh)?\s*(.*?)```", content, re.DOTALL)
    
    code = match.group(1).strip() if match else content.strip()
    
    if code and not code.startswith("#!/bin/bash"):
        code = "#!/bin/bash\n" + code
    return code

def test_case_finder(response_content: Union[str, Any]) -> Dict[str, str]:
    """Extracts input/output pairs from XML-like tags."""
    content = str(response_content)
    test_cases = {}
    for i in range(1, 4):
        input_match = re.search(rf"<input{i}>(.*?)</input{i}>", content, re.DOTALL)
        output_match = re.search(rf"<output{i}>(.*?)</output{i}>", content, re.DOTALL)
        if input_match and output_match:
            test_cases[f"input{i}"] = input_match.group(1).strip()
            test_cases[f"output{i}"] = output_match.group(1).strip()
    return test_cases

def description_finder(response_content: Union[str, Any]) -> str:
    """Extracts the description from <description> tags."""
    content = str(response_content)
    match = re.search(r"<description>(.*?)</description>", content, re.DOTALL)
    return match.group(1).strip() if match else content.strip()

def to_reverse_finder(history_file_path: Path) -> str:
    """Extracts the original mutation description from a history file."""
    try:
        with open(history_file_path, "r") as f:
            history_data = json.load(f)
        return history_data['messages'][1]['content'].split('\n\n')[0]
    except (FileNotFoundError, KeyError, IndexError, json.JSONDecodeError) as e:
        logger.error(f"Could not find/parse reverse description from {history_file_path}: {e}")
        return ""

# --- Core Logic Functions ---

def run_mutator_script(mutator_path: Path, input_file_path: Path) -> str:
    """Executes a mutator script and returns stderr on error."""
    try:
        result = subprocess.run(
            ["bash", str(mutator_path), str(input_file_path)],
            check=True, env=sed_env, capture_output=True, text=True, timeout=10
        )
        return ""
    except subprocess.CalledProcessError as e:
        logger.warning(f"Mutator script {mutator_path.name} failed. Stderr: {e.stderr.strip()}")
        return e.stderr.strip()
    except subprocess.TimeoutExpired:
        logger.warning(f"Mutator script {mutator_path.name} timed out.")
        return "Error: Script execution timed out after 10 seconds."

def get_diff_summary(file1_path: Path, file2_path: Path) -> str:
    """Compares two files and returns a unified diff."""
    content1 = file1_path.read_text().splitlines()
    content2 = file2_path.read_text().splitlines()
    diff = list(difflib.unified_diff(content1, content2, fromfile=str(file1_path), tofile=str(file2_path), lineterm=""))
    return "\n".join(diff) if diff else "No Difference"

def get_paired_inputs(bug_report_path: Path, negative_code_path: Path):
    """Yields base filenames for pairs of buggy/negative code."""
    for c_file in sorted(bug_report_path.glob("*.c")):
        if (negative_code_path / f"{c_file.stem}-negative.c").exists():
            yield c_file.stem

# --- 4. GRAPH STATE DEFINITION ---

class GraphState(TypedDict):
    """State for the graph."""
    base_name: str
    initial_code: str
    target_code: str
    mutation_description: str
    test_cases: Dict[str, str]
    mutator_script: str
    mutator_path: Path
    iteration: int
    error_message: str
    diff_summary: str
    selected_mutator_template_content: str

class ProcessResult(TypedDict):
    """Result object for each parallel process."""
    base_name: str
    status: Literal["SUCCESS", "FAILURE", "SKIPPED"]
    final_mutator_path: str
    iterations: int
    final_message: str

# --- 5. AGENT NODE FUNCTIONS ---
# NOTE: All node functions now access global paths set in the main block.

def description_creator_node(state: GraphState) -> Dict[str, Any]:
    """Generates description, test cases, and the initial mutator script."""
    base_name = state["base_name"]
    to_reverse_path = negative_code_path / f"{base_name}-history.json"
    description_to_reverse = to_reverse_finder(to_reverse_path)

    if not description_to_reverse:
        return {"error_message": "Failed to get description to reverse."}

    # This prompt is now a single, consolidated prompt for the first step.
    prompt = f"""
    You are a C code mutation expert, specializing in creating **generic** `sed` scripts.

    **TASK 1: GENERALIZE MUTATION**
    Reverse the following specific description into a general rule, avoiding specific names or values.
    Respond ONLY with the text inside `<description>` tags.
    
    EXAMPLE:
    Input: "In function 'foo', change the type of parameter 'bar' from 'const int*' to 'int*'."
    Output: <description>Add a 'const' qualifier to a pointer type in a function parameter.</description>

    Description to Reverse:
    ```
    {description_to_reverse}
    ```

    If no description provided, summarize from the original code pair ( Input -> Output ):

    **TASK 2: CREATE TEST CASES**
    Based on the general rule you just created, provide three new, varied input/output C code pairs.
    The transformation from input to output MUST match the rule.
    Format your response EXACTLY as shown, with no extra text:
    <input1>...</input1><output1>...</output1>
    <input2>...</input2><output2>...</output2>
    <input3>...</input3><output3>...</output3>

    **TASK 3: GENERATE MUTATOR SCRIPT**
    Create a single, **generic** Bash script using `sed` that performs the mutation.
    This script must correctly transform all three test cases AND the original example pair below.
    
    GUIDELINES:
    1.  **Generic `sed`**: Use regular expressions. Do NOT hardcode names/values.
    2.  **In-place Edit**: Use `sed -i`. The target file is the first argument (`$1`).
    3.  **Complete Script**: Provide the full script in a single `<code>` block. No comments and explanations. DO not write non-generic code specific for each test case!

    Original Example Pair:
    - Input:
    ```c
    {state["target_code"]}
    ```
    - Output:
    ```c
    {state["initial_code"]}
    ```
    
    Reference Script Example:
    ```bash
    {state["selected_mutator_template_content"]}
    ```
    """

    response = llm.invoke([HumanMessage(content=prompt)])
    response_content = safe_get_content(response)
    log_llm_interaction(prompt, response_content, "description_creator")

    description = description_finder(response_content)
    test_cases = test_case_finder(response_content)
    mutator_script = bash_code_finder(response_content)

    if not all([description, len(test_cases) == 6, mutator_script]):
        return {"error_message": "LLM failed to generate all required initial assets."}

    create_copy(description, descriptions_path / f"{base_name}.txt")
    for name, content in test_cases.items():
        folder = input_test_cases if "input" in name else output_test_cases
        create_copy(content, folder / f"{base_name}-{name}.c")
    
    mutator_path = generated_mutators_path / f"{base_name}.sh"
    create_copy(mutator_script, mutator_path)

    return {
        "mutation_description": description,
        "test_cases": test_cases,
        "mutator_script": mutator_script,
        "mutator_path": mutator_path,
        "iteration": 0,
    }

def test_and_evaluate_node(state: GraphState) -> Dict[str, Any]:
    """Tests the mutator script and evaluates its correctness."""
    iteration = state.get("iteration", 0) + 1
    base_name = state["base_name"]
    mutator_path = state["mutator_path"]

    if iteration > MAX_REFINEMENT_ITERATIONS:
        return {"error_message": "Max iterations reached", "iteration": iteration}

    all_inputs = {
        **{f"input{i}": input_test_cases / f"{base_name}-input{i}.c" for i in range(1, 4)},
        "input4": negative_code_path / f"{base_name}-negative.c"
    }
    all_outputs = {
        **{f"output{i}": output_test_cases / f"{base_name}-output{i}.c" for i in range(1, 4)},
        "output4": bug_report_path / f"{base_name}.c"
    }
    
    temp_dir = generated_temp_files_path / f"{base_name}-{os.getpid()}"
    temp_dir.mkdir(parents=True, exist_ok=True)

    script_errors = []
    diffs = []

    for i in range(1, 5):
        key = f"input{i}"
        temp_input_path = temp_dir / f"{key}.c"
        create_copy(remove_c_comments(opener(all_inputs[key])), temp_input_path)

        error = run_mutator_script(mutator_path, temp_input_path)
        if error:
            script_errors.append(f"Error on {key}:\n{error}")
            continue

        temp_output_path = temp_dir / f"expected_output{i}.c"
        create_copy(remove_c_comments(opener(all_outputs[f"output{i}"])), temp_output_path)
        
        run_clang_format(temp_input_path)
        run_clang_format(temp_output_path)

        diff = get_diff_summary(temp_input_path, temp_output_path)
        if diff != "No Difference":
            diffs.append(f"Diff on pair {i}:\n{diff}")
    
    shutil.rmtree(temp_dir) # Cleanup

    if script_errors:
        error_str = "\n".join(script_errors)
        create_copy(mutator_path.read_text(), errored_mutators_path / mutator_path.name)
        return {"error_message": error_str, "diff_summary": "", "iteration": iteration}

    if not diffs:
        create_copy(mutator_path.read_text(), right_mutators_path / mutator_path.name)
        return {"error_message": "", "diff_summary": ""} # Success

    diff_summary = "\n---\n".join(diffs)
    
    if len(diffs) <= 1:
        create_copy(mutator_path.read_text(), partial_right_mutators_path / mutator_path.name)
    else:
        create_copy(mutator_path.read_text(), wrong_mutators_path / mutator_path.name)
        
    return {"error_message": "", "diff_summary": diff_summary, "iteration": iteration}


def general_refiner_node(state: GraphState) -> Dict[str, Any]:
    """Refines the mutator script based on errors or diffs."""
    error_message = state["error_message"]
    diff_summary = state["diff_summary"]
    
    refinement_context = f"The script failed to execute. Errors:\n{error_message}" if error_message \
        else f"The script produced the wrong output. Differences:\n{diff_summary}"

    test_case_context = ""
    for i in range(1, 4):
        test_case_context += f"Input {i}:\n{state['test_cases'][f'input{i}']}\nOutput {i}:\n{state['test_cases'][f'output{i}']}\n\n"

    prompt = f"""
    You are an expert `sed` script debugger.
    The provided script for the goal "{state['mutation_description']}" is faulty.
    
    **Analysis**: {refinement_context}

    **Test Cases**:
    {test_case_context}

    **Task**:
    Rewrite the entire bash script to fix the issue. The script must be **generic** and robust.
    Respond with ONLY the complete, corrected bash script in a `<code>` block.
    No comments and explanations. DO not write non-generic code specific for each test case.

    **Original Script to Refine**:
    ```bash
    {state["mutator_script"]}
    ```
    """
    response = llm.invoke([HumanMessage(content=prompt)])
    response_content = safe_get_content(response)
    log_llm_interaction(prompt, response_content, "general_refiner_node")
    
    refined_script = bash_code_finder(response_content)
    if not refined_script:
        return {"error_message": "Refiner failed to generate code."}

    create_copy(refined_script, state["mutator_path"])
    return {"mutator_script": refined_script}

# --- 6. CONDITIONAL EDGES & GRAPH BUILDER ---

def should_refine(state: GraphState) -> Literal["refine", "end_failure", "end_success"]:
    """Determines the next step after testing."""
    if not state.get("error_message") and not state.get("diff_summary"):
        return "end_success"
    if state.get("iteration", 0) >= MAX_REFINEMENT_ITERATIONS:
        return "end_failure"
    return "refine"

def build_graph():
    """Builds and compiles the LangGraph StateGraph.
    This is called by each worker process to avoid pickling issues.
    """
    workflow = StateGraph(GraphState)
    workflow.add_node("description_creator", description_creator_node)
    workflow.add_node("test_and_evaluate", test_and_evaluate_node)
    workflow.add_node("refiner", general_refiner_node)

    workflow.set_entry_point("description_creator")
    workflow.add_edge("description_creator", "test_and_evaluate")
    workflow.add_edge("refiner", "test_and_evaluate")

    workflow.add_conditional_edges(
        "test_and_evaluate",
        should_refine,
        {"refine": "refiner", "end_success": END, "end_failure": END}
    )
    return workflow.compile()

# --- 7. PARALLEL EXECUTION AND REPORTING ---

def process_file_pair(base_name: str) -> ProcessResult:
    """Worker function to process a single file pair. Runs in a separate process."""
    app = build_graph() # Each process gets its own compiled graph
    logger.info(f"--- Starting process for {base_name} ---")

    if (generated_mutators_path / f"{base_name}.sh").exists():
        return {
            "base_name": base_name, "status": "SKIPPED",
            "final_mutator_path": str(generated_mutators_path / f"{base_name}.sh"),
            "iterations": 0, "final_message": "Mutator already exists."
        }

    selected_mutator_template_content = ""
    if mutator_templates_names:
        template_name = random.choice(mutator_templates_names)
        selected_mutator_template_content = remove_bash_comments(opener(mutator_templates_path / template_name))

    initial_state: GraphState = {
        "base_name": base_name,
        "initial_code": remove_c_comments(opener(bug_report_path / f"{base_name}.c")),
        "target_code": remove_c_comments(opener(negative_code_path / f"{base_name}-negative.c")),
        "selected_mutator_template_content": selected_mutator_template_content,
        "mutation_description": "", "test_cases": {}, "mutator_script": "",
        "mutator_path": Path(), "iteration": 0, "error_message": "", "diff_summary": "",
    }

    final_state = app.invoke(initial_state)

    status: Literal["SUCCESS", "FAILURE"]
    message = ""
    if final_state.get("error_message"):
        status = "FAILURE"
        message = final_state['error_message']
    else:
        status = "SUCCESS"
        message = "Process completed successfully."
    
    return {
        "base_name": base_name, "status": status,
        "final_mutator_path": str(final_state.get("mutator_path", "")),
        "iterations": final_state.get("iteration", 0),
        "final_message": message,
    }

def generate_report(results: list[ProcessResult], result_root: Path):
    """Generates a CSV report from the processing results."""
    report_path = result_root / f"processing_report_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
    print(f"\n--- Generating Report ---\nSaving report to: {report_path}")

    header = ["base_name", "status", "iterations", "final_mutator_path", "final_message"]
    with open(report_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=header)
        writer.writeheader()
        writer.writerows(results)
    print("[SUCCESS] Report generated.")

# --- MAIN EXECUTION ---
if __name__ == "__main__":
    setup_logger()
    print("[~] Code is Running ... \n")

    config = read_config_file(config_path)
    
    # Define all paths globally so worker processes can access them
    bug_report_path = Path(config["data_root_path"]) / config["bug_report"]
    negative_code_path = Path(config["data_root_path"]) / config["negative_code"]
    result_root_path = Path(config["result_root_path"])
    generated_temp_files_path = result_root_path / config["temp_files"]
    generated_mutators_path = result_root_path / config["generated_mutators"] / config["all_mutators"]
    right_mutators_path = result_root_path / config["generated_mutators"] / config["right_mutators"]
    partial_right_mutators_path = result_root_path / config["generated_mutators"] / config["partial_right_mutators"]
    wrong_mutators_path = result_root_path / config["generated_mutators"] / config["wrong_mutators"]
    errored_mutators_path = result_root_path / config["generated_mutators"] / config["errored_mutators"]
    generated_test_cases_path = result_root_path / config["generated_test_cases"]
    descriptions_path = generated_test_cases_path / config["mutator_descriptions"]
    input_test_cases = generated_test_cases_path / config["input_test_cases"]
    output_test_cases = generated_test_cases_path / config["output_test_cases"]
    mutator_templates_path = SCRIPT_DIR / config["mutator_templates"]
    mutator_templates_names = [f.name for f in mutator_templates_path.glob("*") if f.is_file()]

    # Create necessary directories
    for p in [generated_mutators_path, right_mutators_path, wrong_mutators_path, errored_mutators_path,
              partial_right_mutators_path, generated_temp_files_path, descriptions_path, input_test_cases, output_test_cases]:
        p.mkdir(parents=True, exist_ok=True)
    
    paired_inputs = list(get_paired_inputs(bug_report_path, negative_code_path))
    random.shuffle(paired_inputs)
    results = []
    

    print(f"--- Starting Parallel Processing for {len(paired_inputs)} file pairs using up to {MAX_WORKERS} workers ---")

    with concurrent.futures.ProcessPoolExecutor(max_workers=MAX_WORKERS) as executor:
        future_to_basename = {executor.submit(process_file_pair, base_name): base_name for base_name in paired_inputs}

        for future in tqdm(concurrent.futures.as_completed(future_to_basename), total=len(paired_inputs), desc="Processing Files"):
            base_name = future_to_basename[future]
            try:
                results.append(future.result())
            except Exception as exc:
                logger.critical(f"{base_name} generated a critical exception: {exc}", exc_info=True)
                results.append({
                    "base_name": base_name, "status": "FAILURE",
                    "final_mutator_path": "", "iterations": 0,
                    "final_message": f"Critical exception in worker: {exc}",
                })

    print(f"\n[~] All {len(paired_inputs)} file pairs have been processed.")
    
    if results:
        generate_report(results, result_root_path)

    logger.info("--- All files processed. Ending session. ---")
