# IssueMut

IssueMut is a compiler fuzzing mutator mining tool. It extracts mutation operators from historical compiler bug reports and retrofits such mutators into existing mutational compiler fuzzers. The approach is described in our MSR 2026 paper, **"Learning Compiler Fuzzing Mutators from Historical Bugs"**.

The tool is structured in two parts:

- **Mutator Mining**: Scrapes test cases from bug reports, extracts negative test cases, and generates mutators via LangChain-based pipeline
- **Fuzzer Integration**: Incorporates the mined mutators into existing mutational fuzzing frameworks
  - Docker image is available on [Docker Hub](https://hub.docker.com/r/issuemut/issuemut/tags).

## Repository Structure
```
├── experiment_data/          # Experimental data in our MSR paper
│   ├── Evaluation/           # Evaluation results for RQ1, RQ2, RQ3, and RQ4 (including reported bugs)
│   └── Fuzz4All/             # The results of running Fuzz4All
├── mined_data/               # Mined bug reports, negative test cases, and mutators
│   ├── gcc/
│   └── llvm/
└── src/                      # Implementation of IssueMut
    ├── mutator_mining/       # The code for GCC/LLVM bug report extractor, negative test case generator, and langchain-based mutator generator
    └── fuzzer/               # The code for enhanced fuzzer
        ├── metamut_i/        # MetaMut integration patches and scripts
        └── kitten_i/         # Kitten integration patches and scripts
```

## Prerequisites
- Python 3.11
- Required Python dependencies:
```console
pip install -r src/mutator_mining/requirements.txt
```

- (Optional) For fuzzer integration dependencies, please check [here](src/fuzzer/README.md).

## Mutator Mining Steps

### 1. Scrape GCC/LLVM Bug Reports
This step retrieves bug-triggering test cases and associated metadata (bug descriptions and comments) from compiler bug reports.
```console
# GCC
~/IssueMut/src/mutator_mining$ python3 gcc_bug_report_extractor.py --out_folder=<out_folder> --start_date=<YYYY-MM-DD> --end_date=<YYYY-MM-DD>

# LLVM
~/IssueMut/src/mutator_mining$ python3 llvm_bug_report_extractor.py --out_folder=<out_folder> --start_date=<YYYY-MM-DD> --end_date=<YYYY-MM-DD>
```

### 2. Extract Negative Test Cases
This step generates negative test cases based on the extracted bug-triggering programs. Please update the following configs before running:
```python
# CONFIGS
llm_vendor = "openai"
model = "gpt-4o-mini"
bug_report_directory = "../../mined_data/llvm/bug_report"
out_folder = "llvm_negative_test_case"
```

Run the generator:
```console
~/IssueMut/src/mutator_mining$ python3 negative_test_case_generator.py
```

### 3. Generate Mutators
This step synthesizes fuzzing mutators from mined bug reports using a LangChain-based pipeline. Before running, update the paths in `src/mutator_mining/langchain-issuemut/scripts/config.txt` to point to your bug report and negative test case directories.
```console
~/IssueMut/src/mutator_mining$ cd langchain-issuemut/scripts
~/IssueMut/src/mutator_mining/langchain-issuemut/scripts$ bash run_parallel.sh
```

## Fuzzer Integration
We integrated our mined mutators into mutational fuzzing frameworks MetaMut[1] and Kitten[2].
Please refer to [here](src/fuzzer/README.md) for detailed integration instructions.

[1]: https://github.com/icsnju/MetaMut/tree/gh-pages
[2]: https://github.com/uw-pluverse/perses/tree/master/kitten