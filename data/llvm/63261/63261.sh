#!/bin/bash


# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi


file="$1"


# Update mutex acquire and acquired callback function conditions (handling multi-line patterns)
# :a;N;$!ba: reads the entire input into memory by concatenating all lines into the pattern space.
sed -i -E 's/\|\| [a-zA-Z_][a-zA-Z0-9_]* == [a-zA-Z_][a-zA-Z0-9_]*//' "$file"