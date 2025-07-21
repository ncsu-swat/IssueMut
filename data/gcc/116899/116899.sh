#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file_to_process="$1"

# This script corrects a faulty modulo-assignment operation.
# The regex identifies the pattern `%= ... 1`, where `...` can be whitespace
# or a C-style cast, and changes the `1` to a `0`.
# The original script was flawed because its main capture group was too broad
# and could incorrectly modify identifiers containing the digit 1 (e.g., var_1).
#
# This corrected version ensures that the literal '1' is preceded by a character
# that cannot be part of an identifier (like a space or parenthesis), making the
# substitution safer.
#
# Regex breakdown: s|...|...|
#
# 1. Capture Group 1: `(%=[[:space:]()[:alnum:]_]*)`
#    - Matches the `%=` operator and the characters that can legally appear
#      in a C cast between the operator and the operand. This includes
#      parentheses, letters, numbers, and underscores, which handles
#      types like `(long)` or `(_BitInt(255))`.
#
# 2. Pre-operand boundary: `([^[:alnum:]_])`
#    - This is the key fix. It captures the single character immediately
#      before the literal '1'.
#    - The character class `[^[:alnum:]_]` matches any character that is NOT
#      a letter, number, or underscore. This ensures that the '1' is not
#      the trailing part of an identifier (like `var_1`) or another number
#      (like `11`).
#
# 3. Target literal: `1\b`
#    - Matches the literal '1' followed by a word boundary to ensure we don't
#      match the '1' in '10'.
#
# 4. Capture Group 3: `([[:space:]]*[;),])`
#    - Matches the expression's terminator: optional whitespace followed by a
#      semicolon, closing parenthesis, or comma.
#
# 5. Replacement: `\1\20\3`
#    - `\1`: The captured prefix (e.g., `%= ` or `%= (long)`).
#    - `\2`: The captured boundary character (e.g., a space or `)`).
#    - `0`: The new literal value.
#    - `\3`: The captured suffix (the terminator).

sed -i -E 's|(%=[[:space:]()[:alnum:]_]*)([^[:alnum:]_])1\b([[:space:]]*[;),])|\1\20\3|' "$file_to_process"