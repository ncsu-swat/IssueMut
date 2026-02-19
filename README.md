# IssueMut

IssueMut is a compiler fuzzing mutator mining tool. It extracts mutation operators from historical compiler bug reports and retrofits such mutators into existing mutational compiler fuzzers. The approach is described in our MSR 2026 paper, **"Learning Compiler Fuzzing Mutators from Historical Bugs"**.

The tool is structured in two parts:

- **Mutator Mining**: Scrapes test cases from bug reports, extracts negative test cases, and generates mutators via LangChain-based pipeline
- **Fuzzer Integration**: Incorporates the mined mutators into existing mutational fuzzing frameworks

## Repository Structure
```
├── experiment_data/          # Experimental data in our MSR paper
│   ├── Evaluation/           # Evaluation results for RQ1, RQ2, RQ3, and RQ4 (including reported bugs)
│   ├── Fuzz4All/             # The results of running Fuzz4All
├── mined_data/               # Mined bug reports, negative test cases, and mutators
│   ├── gcc/
│   ├── llvm/
├── src/                      # Implementation of IssueMut
│   ├── mutator_mining/       # The code for GCC/LLVM bug report extractor, negative test case generator, and langchain-based mutator generator
│   ├── fuzzer/               # The code for enhanced fuzzer
```

## Prerequisite
- Python: 3.11
- Required Python dependencies
Install dependencies:
```console
pip install -r src/mutator_mining/requirements.txt
```
- (Optional) dependencies for fuzzer integration please check here(link).

## Mutator Mining Steps
### 1. Scrape GCC/LLVM bug reports
This step retrieves bug-triggering test cases and associated metadata (bug descriptions and comments) from compiler bug reports.

```console
# GCC
~/IssueMut/src/mutator_mining$ python3 gcc_bug_report_extractor.py --out_folder=<out_folder> --start_date=<YYYY-MM-DD> --end_date=<YYYY-MM-DD>

# LLVM
~/IssueMut/src/mutator_mining$ python3 llvm_bug_report_extractor.py --out_folder=<out_folder> --start_date=<YYYY-MM-DD> --end_date=<YYYY-MM-DD>
```
### 2. Extract negative test case
This step generates negative test cases based on the extracted bug-triggering programs.

```console
~/IssueMut/src/mutator_mining$ python3 negative_test_case_generator.py
```
### 3. Generate mutators
This step synthesizes fuzzing mutators from mined bug reports using a langchain-based pipeline.

```console
~/IssueMut/src/mutator_mining$ cd langchain-issuemut/scripts
~/IssueMut/src/mutator_mining/langchain-issuemut/scripts$ bash run_parallel.sh
```

## Fuzzer Integration
We integrated our mined mutators into mutaitonal fuzzing frameworks MetaMut and kitten.
Please refer to src/fuzzer/README.md for detailed integration instructions.