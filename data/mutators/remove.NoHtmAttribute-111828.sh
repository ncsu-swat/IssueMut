#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Use sed to add "long long a, long long b," to the existing parameters and insert lines after the opening brace
sed -i -E 's/__attribute__(.*),+\s*target\s*\(\s*"no-htm"\s*\)(.*)/__attribute__\1\2/' "$file"
sed -i -E 's/__attribute__\s*\(\s*\(\s*target\s*\(\s*"no-htm"\s*\)\s*\)//' "$file"
sed -i -E 's/__attribute__\s*\(\s*\(\s*target\s*\(\s*"no-htm"\s*\)\s*,(.*)/__attribute__\(\(\1/' "$file"