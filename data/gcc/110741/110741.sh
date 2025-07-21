#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

sed -i -E '
# Read the whole file into pattern space to handle multi-line patterns.
1h; 1!H; $!d; g

# Replace newlines with a sentinel character to simplify multi-line matching.
s/\n/\x01/g

# Rule for count_set_bits: replace body with a single-line intrinsic call.
# This pattern captures the signature (\1) and parameter name (\3).
# It robustly matches any simple function body (no nested braces) using `\{[^}]*\}`.
s/(\w+[ \t\x01]+count_set_bits[ \t\x01]*\((.*[ \t\x01]+(\w+))\))[ \t\x01]*\{[^}]*\}/\1 { return __builtin_popcountll(\3); }/g

# Rule for byte_swap: replace body with a single-line intrinsic call.
s/(\w+[ \t\x01]+byte_swap[ \t\x01]*\((.*[ \t\x01]+(\w+))\))[ \t\x01]*\{[^}]*\}/\1 { return __builtin_bswap32(\3); }/g

# Rule for square_root: replace body with a single-line intrinsic call.
s/(\w+[ \t\x01]+square_root[ \t\x01]*\((.*[ \t\x01]+(\w+))\))[ \t\x01]*\{[^}]*\}/\1 { return __builtin_sqrtf(\3); }/g

# Rule for VSXTernaryLogic: This is a more complex case with multiple parameters.
# The regex is designed to be robust by matching the function by name and then
# extracting the actual parameter names from the signature, rather than hardcoding them.
# This makes the script generic and resilient to changes in parameter naming.
# \1 captures the full signature, and \2, \3, \4, \5 capture the four parameter names.
s/([^{]*VSXTernaryLogic[ \t\x01]*\([^,]+[ \t\x01]+(\w+)\s*,\s*[^,]+[ \t\x01]+(\w+)\s*,\s*[^,]+[ \t\x01]+(\w+)\s*,\s*[^,]+[ \t\x01]+(\w+)\s*\))[ \t\x01]*\{[^}]*\}/\1 {\x01  return vec_ternarylogic(\2, \3, \4, \5);\x01}/g

# Restore newlines from the sentinel character.
s/\x01/\n/g
' "$1"