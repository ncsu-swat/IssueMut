#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/"\+x"(\s*\([^)]*\))/"\+f"\1/' "$file"