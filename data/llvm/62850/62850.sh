#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\b([a-zA-Z_][a-zA-Z0-9_]*)_(inner|local|block|scoped)\b/\1/g' "$file"