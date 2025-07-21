#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Add (unsigned int) casting to macro
sed -i -E 's/#define ([a-zA-Z_]\w*) /#define \1 (unsigned int)/' "$file"
