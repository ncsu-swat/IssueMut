# GCC-related Data

This folder contains a collection of GCC bug reports, test cases, negative test cases, and mutators.

## Main Structure

This folder is organized around GCC bug report IDs. Each bug report has its own folder named after its ID number.

```
/
├── {id}/           # Folders named with GCC bug report IDs
├── {id}/           # More bug report folders
├── ...
└── remaining_bug_report/  # Contains bug reports not made to mutators
```

## Bug Report ID Folders

Each `{id}` folder corresponds to a specific GCC bug report, which can be viewed at `https://gcc.gnu.org/bugzilla/show_bug.cgi?id={id}`. 

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
