#!/bin/bash


# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi


file="$1"


# Find 'strtol(..., ..., 10)' and replace the last argument with 0
# \10 (\1 refers to everything inside the first capture group (...), the 0 at the end replaces 10)
sed -i -E 's/(strtol\(.*, *&[a-zA-Z_][a-zA-Z0-9_]*, *)10/\10/' "$file"