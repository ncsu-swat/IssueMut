#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E -z 's/if\s*\(([^)]+)\)\s*\{\s*([a-zA-Z0-9_]+)\s*=\s*1\s*;\s*\}\s*else\s*\{\s*(.*\S)\s+([a-zA-Z0-9_]+)\s*=\s*([^;]+);\s*\2\s*=\s*\(\s*\4\s*\?\s*\4\s*:\s*([^)]+)\)\s*!=\s*0\s*;\s*\}/\2 = \1 || \5 ?: \6;/g' "$file"