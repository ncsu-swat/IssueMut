#!/bin/bash


# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi


file="$1"


# Replace "char *p = NULL;" with "void *p = NULL;"
sed -i -E 's/^ *char \*/void \*/g' "$file"