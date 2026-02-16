# Mined Data Directory

This directory contains mined bug reports, generated negative test cases, and fuzzer-ready mutators for GCC and LLVM.

Unlike the `msr-2026` artifact branch , which organizes data per bug ID in individual folders, this branch uses a stage-oriented layout aligned with the IssueMut tool pipeline.

---

## Directory Structure
```
mined_data/
├── gcc/
│   ├── bug_report/
│   ├── negative_test_case/
│   └── mutators/
├── llvm/
│   ├── bug_report/
│   ├── negative_test_case/
│   └── mutators/
```
For each compiler:

### `bug_report/`

Contains extracted test cases and bug report descriptions:

- `{id}.c` — Test case extracted from the bug report
- `{id}.txt` — Bug report description/content

Each `{id}` corresponds to the original compiler bug report:
- GCC: `https://gcc.gnu.org/bugzilla/show_bug.cgi?id={id}`
- LLVM: `https://github.com/llvm/llvm-project/issues/{id}`

---

### `negative_test_case/`

Contains generated negative test cases:

- `{id}-negative.c` — Negative test case derived from bug `{id}`

These are produced by the `mutator_mining` component.

---

### `mutators/`

Contains fuzzer-ready mutators derived from bug reports:

- `{id}.yaml` (or `.cpp`) — Mutator generated from bug `{id}`

Mutators are directly consumed by the `fuzzer` component.

A mutator corresponds to a bug report via the shared `{id}` postfix.

---

## Bugs Without Mutators

IssueMut does not necessarily generate a mutator for every mined bug report.

If no file with the same `{id}` exists in the `mutators/` directory, it indicates that no mutator was created for that bug report.

For the complete list of mined bug reports that were not converted into mutators, please refer to the `msr-2026` artifact branch:

- GCC: https://github.com/ncsu-swat/IssueMut/tree/msr-2026/data/gcc/remaining_bug_report  
- LLVM: https://github.com/ncsu-swat/IssueMut/tree/msr-2026/data/llvm/remaining_bug_report