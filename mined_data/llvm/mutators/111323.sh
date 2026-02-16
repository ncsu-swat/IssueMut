#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

info=$(sed -n -E 's/^\s*(const\s+)?[a-zA-Z0-9_ \t*]*\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*=\s*([0-9a-fxA-FXULf.]+);/\2@\3/p' "$file" | head -n 1)

if [ -n "$info" ]; then
    var="${info%@*}"
    const="${info#*@}"

    sed -i -E \
        -e "/\b$var\b\s*=\s*.*${const}.*;/d" \
        -e "s/\b$var\b/$const/g" \
        "$file"
fi