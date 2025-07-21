#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
s/(^[[:space:]]*|[[:space:]]*[(,][[:space:]]*)(\bU\b)([[:space:]]+[a-zA-Z0-9_]+[[:space:]]*[={[])/\1typename \2::value_type\3/;
s/(^[[:space:]]*|[[:space:]]*[(,][[:space:]]*)(\bV\b)([[:space:]]+[a-zA-Z0-9_]+[[:space:]]*[={[])/\1typename \2::inner_type\3/;
s/(^[[:space:]]*|[[:space:]]*[(,][[:space:]]*)(\bNumber\b)([[:space:]]+[a-zA-Z0-9_]+[[:space:]]*[={[])/\1typename \2::result_type\3/;
' "$file"