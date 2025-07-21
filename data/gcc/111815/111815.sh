#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script incorrectly used non-greedy matching `.*?` which splits an
# expression at the first `+` operator. To correctly identify the last two terms
# of an addition, we need to split at the last possible `+` operator. This is
# the default behavior of the greedy `.*` quantifier in sed. By replacing all
# instances of `.*?` with `.*`, the regex correctly partitions the expressions.
#
# For an expression like `(A + B + C) + D`, the corrected first rule will match:
# \1 = A + B
# \2 = C
# \3 = D
# This correctly identifies the terms inside the parentheses and the term outside,
# leading to the transformation `(A + B) + D + C`.
#
# For an unparenthesized expression like `return A + B + C + D;`, the corrected
# third rule will match:
# \1 = return A + B
# \2 = C
# \3 = D
# This correctly identifies the last two terms of the entire expression, leading
# to the transformation `return A + B + D + C;`.
#
# The second rule is also corrected to use greedy matching to handle cases like
# `A + B + (C + D)`, correctly identifying `A + B` as the first part.

sed -i -E \
    -e 's/^[[:space:]]*return[[:space:]]*\((.*)[[:space:]]*\+[[:space:]]*(.*)\)[[:space:]]*\+[[:space:]]*(.*);/return \1 + \3 + \2;/;t' \
    -e 's/^[[:space:]]*return[[:space:]]*(.*)[[:space:]]*\+[[:space:]]*\((.*)[[:space:]]*\+[[:space:]]*(.*)\);/return \1 + \3 + \2;/;t' \
    -e 's/^[[:space:]]*(return[[:space:]]+.*)[[:space:]]*\+[[:space:]]*(.*)[[:space:]]*\+[[:space:]]*(.*);/\1 + \3 + \2;/' \
    "$file"