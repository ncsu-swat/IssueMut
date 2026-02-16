#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(for[[:space:]]*\([[:space:]]*((const|unsigned|signed)[[:space:]]+)*[[:space:]]*)\bint\b/\1long/' "$file"