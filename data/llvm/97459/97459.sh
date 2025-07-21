#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -E -i 's/union(.*)\{0\}/union\1{}/' $file
sed -E -i 's/struct(.*)\{0\}/struct\1{}/' $file