#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

temp_file=$(mktemp)
cp "$file" "$temp_file"

CANDIDATE_IDS=$( (
    sed -nE 's/.*for\s*\([^;]*;[[:space:]]*\b([a-zA-Z_][a-zA-Z0-9_]*)\b[[:space:]]*>=.*/\1/p' "$temp_file"
    sed -nE 's/.*for\s*\([^=]*=[[:space:]]*\b([a-zA-Z_][a-zA-Z0-9_]*)\b[[:space:]]*-.*/\1/p' "$temp_file"
    sed -nE 's/.*\[[[:space:]]*\b([a-zA-Z_][a-zA-Z0-9_]*)\b[[:space:]]*\].*/\1/p' "$temp_file"
) | sort -u)

for ID in $CANDIDATE_IDS; do
    sed -i -E "/\bfor\s*\(/! s/\b(int)\s+(\b$ID\b)/unsigned \2/" "$file"
done

rm "$temp_file"