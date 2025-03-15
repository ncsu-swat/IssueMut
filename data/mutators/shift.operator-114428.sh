#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E "s/>>\s*(.*)/>> \(short\)\1/g" "$file"

sed -i -E "s/\(\(.*\)(.*)\)\s*>>/\1 >>/g" "$file"
