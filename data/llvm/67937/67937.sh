#!/bin/bash


# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi


file="$1"


# Replace "struct d : c {};" with "struct d : virtual c {};"
sed -i -E 's/struct ([a-zA-Z_][a-zA-Z0-9_]*) : ([a-zA-Z_][a-zA-Z0-9_]*)/struct \1 : virtual \2/g' "$file"