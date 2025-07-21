#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/^[[:space:]]*goto[[:space:]]+[a-zA-Z0-9_]+[[:space:]]*;.*$//' "$file"