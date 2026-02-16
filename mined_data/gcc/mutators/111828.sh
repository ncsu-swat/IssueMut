#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/__attribute__.*target/ {
    :a
    s/\btarget\b\s*\([^)]+\)\s*,\s*//; t a
    s/,\s*\btarget\b\s*\([^)]+\)//; t a
    s/__attribute__\s*\(\(\s*\btarget\b\s*\([^)]+\)\s*\)\)//
    s/__attribute__\s*\(\(\s*\)\)//
}
' "$file"