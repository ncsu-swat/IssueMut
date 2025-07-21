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
|-- data                         # Data directory containing evaluation results, mutators, seeds, and compiler-specific files
|   |-- Evaluation               # Evaluation results for RQ1, RQ2, RQ3, and RQ4 (including reported bugs)
|   |-- seeds.tar.gz             # Seed programs
|   |-- gcc                      # GCC compiler-related data (including test cases from bug reports, bug report contents, negative test cases, and mutators)
|   |-- llvm                     # LLVM compiler-related data (including test cases from bug reports, bug report contents, negative test cases, and mutators)
|-- src                          # The implementation directory
|   |-- mutator_mining           # The code for GCC/LLVM bug report extractor, negative input generator, and langchain-based mutator generator
|   |-- fuzzer                   # The code for enhanced fuzzer
|   |   |-- issuemut.patch       # The patch file to support MetaMut for bash scripts and the setup for the compilers that we used for experiments
|   |   |-- MutatorUsingBash.h   # The header file that extend MetaMut for bash scripts
|   |   |-- MutatorUsingBash.cpp # The code to extend MetaMut for bash scripts
|   |   |-- replaceOne.sh        # Bash script using grep, awk, and sed to perform mutations
|-- Fuzz4All                     # The results of running Fuzz4All
```
