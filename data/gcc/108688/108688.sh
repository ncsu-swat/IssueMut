#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E '
:a;
N;
$!ba;
s/\<volatile\>([[:space:]]*\n[[:space:]]*\<union\>)/\1/g;
s/\<volatile\>[[:blank:]]+\<union\>/union/g;
' "$file"