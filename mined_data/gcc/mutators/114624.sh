#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\bvolatile\s+//g; s/\s+\bvolatile\b//g' "$file"

sed -i -E '
/^\s*(typedef|struct|union|enum)[^;]*\{/,/^\s*}/b

:merge_loop
$b

N

s/^([ \t]*)(.*)\s+([^\s,;=]+)\s*;\s*\n\1\2\s+([^;]+);\s*$/\1\2 \3, \4;/

t merge_loop

P
D
' "$file"