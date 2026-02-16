#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '/^[[:space:]]*(__asm__|asm)([[:space:]]+(__volatile__|volatile))?[[:space:]]*\([[:space:]]*""[[:space:]]*:[[:space:]]*:[[:space:]]*:[[:space:]]*[^)]*"memory"[^)]*\)[[:space:]]*;.*$/d' "$file"