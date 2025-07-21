#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\s*\*\s*\(\s*1(\.[0-9]*)?[fL]?\s*\/\s*([^)]+)\s*\)/ \/ \2/' "$file"