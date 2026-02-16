#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(\S.*?)\s*=\s*!\s*\(?\s*\1\s*\)?\s*;/ \1 = \1 == 0;/g' "$file"