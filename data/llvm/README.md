# LLVM-related Data

This folder contains a collection of LLVM bug reports, test cases, negative test cases, and mutators.

## Main Structure

This folder is organized around LLVM bug report IDs. Each bug report has its own folder named after its ID number.

```
/
├── {id}/           # Folders named with LLVM bug report IDs
├── {id}/           # More bug report folders
├── ...
└── remaining_bug_report/  # Contains bug reports not made to mutators
```

## Bug Report ID Folders

Each `{id}` folder corresponds to a specific LLVM bug report, which can be viewed at `https://github.com/llvm/llvm-project/issues/{id}`. 

Each folder contains:

```
{id}/
├── {id}.c              # Test case from the bug report
├── {id}.txt            # Bug report content/description
├── {id}-negative.c     # Negative test case
└── *.cpp               # Mutator
```

## Remaining Bug Report Folder

The `remaining_bug_report` folder contains bug reports and test cases that have not been made to mutators:

```
remaining_bug_report/
├── {id}.c      # Test case code
└── {id}.txt    # Bug report content
```
