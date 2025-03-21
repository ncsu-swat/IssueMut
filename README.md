# IssueMut-ICSE2026

This is the replication package for the paper "Bug Histories as Sources of Compiler Fuzzing Mutators" submitted to ICSE'26.

This paper proposes IssueMut, an approach for extracting compiler
fuzzing mutators from bug histories. Our insight is that bug reports
contain hints about program elements that induced compiler bugs,
which can guide fuzzers towards similar bugs. IssueMut uses a
semi-automated method to mine mutators from bug reports and
retrofit such mutators into existing mutational compiler fuzzers.

## Structure of the project

```
|-- data                     # Data directory containing evaluation results, mutators, seeds, and compiler-specific files
|   |-- Evaluation           # Evaluation results for RQ1, RQ2, and RQ3 (including reported bugs)
|   |-- seeds.tar.gz         # Seed programs
|   |-- gcc                  # GCC compiler-related data
|   |   |-- bug_reports      # GCC bug reports
|   |   |-- negative_inputs  # Negative inputs for GCC
|   |   |-- mutators         # Mutators mined from GCC bug reports
|   |-- llvm                 # LLVM compiler-related data
|   |   |-- bug_reports      # LLVM bug reports
|   |   |-- negative_inputs  # Negative inputs for LLVM
|   |   |-- mutators         # Mutators mined from LLVM bug reports
|-- src                      # The implementation directory
|   |-- mutator_mining       # The code for GCC/LLVM bug report extractor and negative input generator
|   |-- MutatorUsingBash.cpp # The code to extend MetaMut for bash scripts
|   |-- replaceOne.sh        # Bash script using grep, awk, and sed to perform mutations
|-- Fuzz4All                 # The results of running Fuzz4All
```
