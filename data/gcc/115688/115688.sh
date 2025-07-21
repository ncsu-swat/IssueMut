#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/target\s*\(\s*"[^"]*,/b
/target\s*\(\s*"altivec"\s*\)/b
s/(target\s*\(\s*"[^",]+)("\s*\))/\1,altivec\2/
' "$file"