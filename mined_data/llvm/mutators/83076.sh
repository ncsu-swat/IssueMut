#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
    -e 's/([^=[:space:]]+)[[:space:]]*==[[:space:]]*0[uUlL]*[[:space:]]*\?[[:space:]]*(.*)[[:space:]]*:[[:space:]]*__builtin_ctz(l|ll|ti)?[[:space:]]*\([[:space:]]*\1[[:space:]]*\)/__builtin_ctzg(\1, \2)/g' \
    -e 's/__builtin_ctz(l|ll|ti)?[[:space:]]*\([[:space:]]*([^)]*)[[:space:]]*\)/__builtin_ctzg(\2)/g' \
    "$file"