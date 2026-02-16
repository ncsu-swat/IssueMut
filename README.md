# IssueMut

This is the replication package for the paper MSR 2026 paper **"Learning Compiler Fuzzing Mutators from Historical Bugs"**.

This paper proposes IssueMut, an approach for extracting compiler
fuzzing mutators from bug histories. Our insight is that bug reports
contain hints about program elements that induced compiler bugs,
which can guide fuzzers towards similar bugs. IssueMut uses a
semi-automated method to mine mutators from bug reports and
retrofit such mutators into existing mutational compiler fuzzers.

## Repository Structure
```
├── experiment_data/          # Experimental data
│   ├── Evaluation/           # Evaluation results for RQ1, RQ2, RQ3, and RQ4 (including reported bugs)
│   ├── Fuzz4All/             # The results of running Fuzz4All
├── mined_data/               # Mined bug reports, negative test cases, and mutators
│   ├── gcc/
│   ├── llvm/
├── src/                      # Implementation of IssueMut
│   ├── mutator_mining/       # The code for GCC/LLVM bug report extractor, negative test case generator, and langchain-based mutator generator
│   ├── fuzzer/               # The code for enhanced fuzzer
```