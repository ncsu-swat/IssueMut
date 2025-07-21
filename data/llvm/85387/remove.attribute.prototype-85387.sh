#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
 
sed -E -i 's/typedef ([a-zA-Z_][a-zA-Z0-9_]*)(( [a-zA-Z_][a-zA-Z0-9_]*)*);/typedef \1\2 __attribute__((aligned(4)));/' $file