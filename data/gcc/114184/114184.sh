#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:a
$!N
s/^([[:space:]]*)(.*[^[:space:]])[[:space:]]+([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*=[[:space:]]*(\{[^}]*\})[[:space:]]*;.*\n([[:space:]]*)(.*[^[:space:]])[[:space:]]*=[[:space:]]*\3\b.*$/\5\6 = (\2)\4;/
ta
P
D
' "$file"