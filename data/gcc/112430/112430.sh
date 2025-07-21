#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:loop
$!N
s/^([ \t]*)[a-zA-Z_][a-zA-Z0-9_ \t*]*\b([a-zA-Z_][a-zA-Z0-9_]*)\b[ \t]*=[ \t]*([^<]*<[^;]*);[ \t]*\n\1(.*?)[ \t]*\+=[ \t]*\b\2\b[ \t]*;/\1\4+= \3;/
t loop

P
D
' "$file"