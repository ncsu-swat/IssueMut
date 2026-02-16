#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Remove stdbool.h header and (bool) casting
sed -i -E 's/#include <stdbool.h>//' "$file"
sed -i -E 's/\(bool\)\(([^)]*)\)/\1/' "$file"