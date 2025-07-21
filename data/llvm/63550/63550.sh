#!/bin/bash


# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi


file="$1"


# Replace "= (int *);" with """";"
sed -i -E 's/= \(int \*\)([0-9]+);/=\1;/' "$file"
