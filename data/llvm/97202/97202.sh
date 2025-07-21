#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -E -i 's/\s+char8_t([^=]*)=/ char\1=/' $file

sed -E -i 's/\s+char8_t([^)]*)\)/ unsigned char\1)/' $file