#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
$!N
/^[[:space:]]*(int|long|short|char|float|double|void|signed|unsigned)[[:space:]]/{
    P
    D
}
s/^([[:space:]]*)(\S.*\S)[[:space:]]+([a-zA-Z_][a-zA-Z0-9_]*);[[:space:]]*\n\1int[[:space:]]+([^;]+);/\1int \3, \4;/
t
P
D
' "$file"