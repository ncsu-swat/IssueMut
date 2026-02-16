#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/^(\s*)(([a-zA-Z_][a-zA-Z0-9_]*)(\[[^]]*\])+)\s*=\s*(.*);/\1*\(volatile typeof(\2) *\)\&\2 = \5;/' "$file"