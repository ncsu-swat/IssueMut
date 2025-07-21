#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E 's/\([[:space:]]*(signed[[:space:]]+long[[:space:]]+long[[:space:]]+int|signed[[:space:]]+long[[:space:]]+long|signed[[:space:]]+long[[:space:]]+int|signed[[:space:]]+short[[:space:]]+int|signed[[:space:]]+int|signed[[:space:]]+long|signed[[:space:]]+short|signed[[:space:]]+char|long[[:space:]]+long[[:space:]]+int|long[[:space:]]+long|long[[:space:]]+int|short[[:space:]]+int|long|short|int|char|signed)[[:space:]]*\)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*(\.|->)[[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*)/\2/g' "$file"