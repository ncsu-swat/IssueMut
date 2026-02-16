#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(^|[^a-zA-Z0-9_\[])([a-zA-Z_][a-zA-Z0-9_]*)\s*([<>]=?|==|!=)\s*(-?[0-9]+)([^.a-zA-Z0-9_])/\1(float)\2 \3 \4.\5/g' "$file"