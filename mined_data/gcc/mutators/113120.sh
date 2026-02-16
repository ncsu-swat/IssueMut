#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's#(\b(if|while)\b\s*\(\s*)([a-zA-Z_][a-zA-Z0-9_]*)(\s*\))#\1\3 != 0\4#' "$file"