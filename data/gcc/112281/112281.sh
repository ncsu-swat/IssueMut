#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Remove volatile from that struct
sed -i -E "s/^\s*\} volatile (.*);/\} \1;/" "$file"