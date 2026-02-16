#!/bin/bash
# This script inspects a C file for specific OpenMP data mapping constructs.
# If any of these constructs are found, the entire file is replaced with a
# standardized template. Otherwise, the file is left unchanged.
#
# The logic is as follows:
# 1. The entire file is read into sed's memory (hold space) using the
#    '1h; 1!H; $!d; g' idiom. This allows the regex to be checked against
#    the whole file at once.
# 2. A series of simple regular expressions checks for each of the target
#    OpenMP data constructs. Using multiple simple patterns is more portable
#    and robust than a single complex one with alternation.
# 3. '/pattern/{b change}': If any pattern is found, sed branches to the
#    ':change' label.
# 4. 'b': If execution reaches this command, it means no patterns were found.
#    The script branches to the end, and the default action is to print the
#    (unmodified) pattern space.
# 5. ':change': This label marks the start of the replacement logic.
# 6. 'c\ text': The 'c' (change) command replaces the entire pattern space
#    with the provided template text. Each newline within the replacement
#    text must be escaped with a backslash, which was the primary error in
#    the original script.

sed -i -e '
1h; 1!H; $!d; g
/#[[:space:]]*pragma omp target data/{b change}
/#[[:space:]]*pragma omp target map/{b change}
/#[[:space:]]*pragma omp target is_device_ptr/{b change}
/#[[:space:]]*pragma omp target enter data/{b change}
/#[[:space:]]*pragma omp target exit data/{b change}
/omp_target_alloc/{b change}
/omp_target_free/{b change}
b
:change
c\
#include <omp.h>\
#include <stdio.h>\
#include <assert.h>\
\
\
\
\
\
\
int main(void) {\
#pragma omp target\
  {\
    \
    \
    printf("Executed on target device without data mapping.\\n");\
  }\
  return 0;\
}
' "$1"