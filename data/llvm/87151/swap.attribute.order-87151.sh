#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
 
sed -E -i 's/__attribute__\(\(([a-zA-Z_]\w*)\)\)\s+([a-zA-Z_]\w*)\s+([a-zA-Z_]\w*)\s*\(([^)]*)\)\s*\{([^}]*)\}/\2 \3(\4) __attribute__((\1)) {\5}/' $file