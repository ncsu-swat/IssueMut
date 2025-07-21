#!/bin/bash

if [ $# -ne 1 ]; then
    exit 1
fi

file="$1"

REPLACEMENT_VAL="65537" # Default value

if grep -q -E "\bunsigned long long\b" "$file"; then
    REPLACEMENT_VAL="1234567"
elif grep -q -E "\blong\b" "$file"; then
    REPLACEMENT_VAL="99999"
elif grep -q -E "\bint\b" "$file"; then
    REPLACEMENT_VAL="40000"
fi

# Pattern 1: Chained assignment, e.g., `var = expr * C; other = var * C;`
# The regex ensures the same variable (`\1`) and constant (`\3`) are used.
# It uses the replacement value determined by the type context.
sed -i -E ':a;N;$!ba; s/([a-zA-Z_][a-zA-Z0-9_]*)(\s*=\s*.*?\*\s*)([0-9]+)(;)((.|\n)*?)(.*?\s*=\s*)\1(\s*\*\s*)\3(;)/\1\2'"$REPLACEMENT_VAL"'\4\5\7\1\8'"$REPLACEMENT_VAL"'\9/g' "$file"

# Pattern 2: Chained expression, e.g., `(expr * C) * C`
# The regex finds a constant (`\2`) that is repeated in the expression.
sed -i -E ':a;N;$!ba; s/(\*\s*)([0-9]+)(\s*\)\s*\*\s*)\2/\1'"$REPLACEMENT_VAL"'\3'"$REPLACEMENT_VAL"'/g' "$file"