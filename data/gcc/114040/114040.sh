#!/bin/bash

# Use a control character as a placeholder to avoid issues with '>>' in the regex.
sed -i 's/>>/\x01/g' "$1"

# This single sed command uses an alternation to handle two observed patterns:
# 1. A parenthesized LHS, which is more specific and matched first.
#    e.g., (((result * val3) >> 32) != 0)
#    Captures: \2=LHS, \3=BITS
# 2. A "bare" LHS (without its own surrounding parentheses), which is more general.
#    e.g., ((a >> 64) != 0)
#    Captures: \5=LHS, \6=BITS
# The replacement uses combined backreferences (\2\5 and \3\6) to construct the
# __builtin_sub_overflow_p call. Since only one side of the alternation can match,
# one set of backreferences will always be empty.
sed -i -E 's/(\(\s*\(\s*\((.*)\)\s*\x01\s*([0-9]+)\)\s*!=\s*0\s*\))|(\(\s*\(\s*([^\x01()]+)\s*\x01\s*([0-9]+)\)\s*!=\s*0\s*\))/__builtin_sub_overflow_p(\2\5, 0, (unsigned _BitInt(\3\6))0)/g' "$1"

# Restore the original '>>' operator.
sed -i 's/\x01/>>/g' "$1"