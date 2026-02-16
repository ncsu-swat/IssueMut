#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E "s/strcpy/sprintf/" "$file"
