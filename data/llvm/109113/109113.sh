#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script replaces a C-style cast with a union-based bitcast.
# It is designed to be robust and handle various spacings and parenthesized expressions.
#
# The script operates in two stages using sed's branching capabilities.
#
# Stage 1: The main transformation.
# The first 's' command identifies lines containing a cast in an assignment, e.g., `var = (type)expr;`.
# - It uses [[:space:]] for portability over the non-standard \s.
# - It captures the Left-Hand Side (LHS), the cast type, and the expression.
#   - Group 1: The LHS part (e.g., "v2di result = ").
#   - Group 2: The type from within the cast parentheses (e.g., "v2di").
#   - Group 3: The expression being cast (e.g., "get_vector()" or "(foo() + bar())").
#     The pattern `(.*[^[:space:];])` robustly captures the expression, trimming trailing whitespace.
# - If a substitution is made, it branches (`t`) to the `:cleanup` label.
#
# Stage 2: The cleanup loop.
# This stage handles cases where the original expression was already parenthesized.
# The transformation would introduce redundant parentheses, e.g., `typeof((expr))`.
# - The two 's' commands in the cleanup block remove one layer of redundant parentheses
#   from the `typeof` and `.s` parts of the new expression.
# - The `t cleanup` command after each substitution creates a loop, ensuring that
#   multiple layers of parentheses (e.g., `(((expr)))`) are all removed.

sed -i -E '
# Stage 1: Find and transform the cast.
# Groups: \1 = LHS, \2 = TYPE, \3 = EXPR
s/^(.*[[:space:]]*=[[:space:]]*)\([[:space:]]*([^)]+)[[:space:]]*\)[[:space:]]*(.*[^[:space:];])[[:space:]]*;/\1((union { typeof(\3) s; \2 d; }){ .s = (\3) }).d;/
t cleanup

# If no substitution, skip cleanup and move to the next line.
b

# Stage 2: Cleanup loop for extra parentheses.
:cleanup
s/typeof\(\((.*)\)\)/typeof(\1)/; t cleanup
s/(\.s[[:space:]]*=[[:space:]]*)\(\((.*)\)\)/\1(\2)/; t cleanup
' "$file"