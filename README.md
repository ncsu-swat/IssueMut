# IssueMut-ICSE2026

## Structure of the project

```
|-- data                     # Data directory containing evaluation results, mutators, seeds, and compiler-specific files
|   |-- evaluation           # Evaluation results
|   |-- seeds                # Seed programs
|   |-- gcc                  # GCC compiler-related data
|   |   |-- bug_reports      # GCC bug reports
|   |   |-- negative_inputs  # Negative inputs for GCC
|   |   |-- mutators         # Mutators mined from GCC bug reports
|   |-- llvm                 # LLVM compiler-related data
|   |   |-- bug_reports      # LLVM bug reports
|   |   |-- negative_inputs  # Negative inputs for LLVM
|   |   |-- mutators         # Mutators mined from LLVM bug reports
|
|-- src                      # The implementation directory
|   |-- mutator_mining       # The code for GCC/LLVM bug report extractor and negative input generator
|   |-- MutatorUsingBash.cpp # The code to extend MetaMut for bash scripts
|   |-- replaceOne.sh        # Bash script using grep, awk, and sed to perform mutations
|-- Fuzz4All                 # The results of running Fuzz4All
```
