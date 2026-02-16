#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/((==|!=)[[:space:]]*)(\([[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\)[[:space:]]*0)/\10/g' "$file"
sed -i -E 's/((\([[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\)[[:space:]]*0)[[:space:]]*)((==|!=))/0 \4/g' "$file"