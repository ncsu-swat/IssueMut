#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/\[[^]]*-\s*(1[6-9]|[2-9][0-9]|[1-9][0-9]{2,})\s*\]/b
s/(\[[^]]*-\s*)([2-9]|1[0-5])(\s*\])/\116\3/
' "$file"