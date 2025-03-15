#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Use sed to add "long long a, long long b," to the existing parameters and insert lines after the opening brace
sed -i '/^int [a-zA-Z0-9_][a-zA-Z0-9_]* *(.*)/,/^{/{
    s/^int \([a-zA-Z0-9_][a-zA-Z0-9_]*\) *(\(.*\))/int \1 (long long a, long long b, \2)/;
    s/^{/{\n    (void) a;\n    (void) b;/;
}' "$file"

echo "Parameters added and brace handled in file: $file."