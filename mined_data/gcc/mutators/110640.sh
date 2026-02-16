#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/([=,{])([[:space:]]*)([-+]?)(\s*)\b2049\b([ULul]*)?/\1\2\3\465535\5/g' "$file"