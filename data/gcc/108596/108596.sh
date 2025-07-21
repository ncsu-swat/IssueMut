#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -Ez 's/(^|\n)[[:blank:]]*goto[[:blank:]]+([a-zA-Z_][a-zA-Z0-9_]*);[^\n]*(\n[[:blank:]]*)+([[:blank:]]*\2:[^\n]*)/\1\4/g' "$file"