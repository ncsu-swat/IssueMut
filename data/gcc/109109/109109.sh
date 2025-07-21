#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:a; N; $!ba;
:loop
s/\*\s*((\([[:space:]]*(1ULL|ULL_C\(1\))[[:space:]]*<<[[:space:]]*32[[:space:]]*\))|((0x100000000|4294967296)(ULL|ull))|((0x100000000|4294967296)))\s*(\)*)\s*[+]/ << 32\9 | /g
t loop
' "$file"