#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Adds no-prefix to target attribute
sed -i -E "s/__attribute__\(\(target\(\"([^\"]*)\"\)\)\)/__attribute__\(\(target\(\"no-\1\"\)\)\)/" "$file"