#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E '/([a-zA-Z_][a-zA-Z0-9_]*)\[([0-9]+)\] = 0;/N;s/([a-zA-Z_][a-zA-Z0-9_]*)\[([0-9]+)\] = 0;\n[[:space:]]*\1\[([0-9]+)\] = 0;/\(\&\1[0]\)[\2] = \(\&\1[0]\)[\3] = 0;/g' "$file"

sed -i -E 's/__builtin_memset\(([a-zA-Z_][a-zA-Z0-9_]*),[[:space:]]*0,[[:space:]]*sizeof\(\1\)\);/__builtin_memset(\1, 0, 8);/g' "$file"

#TODO do-while wrapper