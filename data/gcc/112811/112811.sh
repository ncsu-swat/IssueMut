#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:a
$!N
s/^[[:space:]]*([a-zA-Z0-9_.*->()]+)\[0\][[:space:]]*=[[:space:]]*'\''\\0'\'';\n(.*[(,][[:space:]]*)\1([[:space:]]*[),].*)/\2\1\3/
ta
s/^[[:space:]]*\*[[:space:]]*([a-zA-Z0-9_.*->()]+)[[:space:]]*=[[:space:]]*'\''\\0'\'';\n(.*[(,][[:space:]]*)\1([[:space:]]*[),].*)/\2\1\3/
ta
P
D
' "$file"