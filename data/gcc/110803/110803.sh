#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The core of the issue is that regular expressions are not powerful enough to
# perfectly parse C code with arbitrarily nested parentheses. The original script
# used a greedy '.*' which is dangerous and also had incorrect backreferences.
# This revised script uses more constrained patterns and correct backreferences.
# It assumes that an operand being cast is either a simple token (like a variable)
# or an expression without parentheses inside, enclosed in one level of parentheses.
# This is a robust heuristic that covers the provided test cases and many common scenarios.

sed -i -E '
:a

# Define the unsigned integer types for the cast.
# Using a variable would be cleaner but less portable for sed.
# So we repeat the pattern.
# Pattern: (unsigned long long|unsigned long|unsigned int|unsigned short|unsigned char|unsigned)

# Case 1: Left operand is of the form ((cast) operand)
# Example: ((unsigned int)x) ^ y
# The [^)]* is a non-greedy way to match the operand, assuming it contains no parentheses.
s/(\(\s*\((unsigned long long|unsigned long|unsigned int|unsigned short|unsigned char|unsigned)\)\s*([^)]*)\s*\))\s*\^/\3 \^/
t a

# Case 2: Right operand is of the form ((cast) operand)
# Example: y ^ ((unsigned int)x)
s/\^\s*(\(\s*\((unsigned long long|unsigned long|unsigned int|unsigned short|unsigned char|unsigned)\)\s*([^)]*)\s*\))/\^ \3/
t a

# Case 3: Left operand is of the form (cast) operand
# Example: (unsigned int)x ^ y
# This fixes a backreference bug in the original script and uses a more robust
# pattern for the operand than just a C identifier.
s/(\((unsigned long long|unsigned long|unsigned int|unsigned short|unsigned char|unsigned)\))\s*([^[:space:];,()^]+)\s*\^/\3 \^/
t a

# Case 4: Right operand is of the form (cast) operand
# Example: y ^ (unsigned int)x
s/\^\s*(\((unsigned long long|unsigned long|unsigned int|unsigned short|unsigned char|unsigned)\))\s*([^[:space:];,()^]+)/\^ \3/
t a

' "$file"