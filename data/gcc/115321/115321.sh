#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

sed -i -E '
:a
$!N
s/^[[:space:]]*__asm__\s*\(""\s*:\s*"\+r".*\);\s*\n(.*__builtin_bswap.*|[[:space:]]*__asm__\s*\(""\s*:\s*"\+r".*\);)/\1/
t a
P
D
' "$1"