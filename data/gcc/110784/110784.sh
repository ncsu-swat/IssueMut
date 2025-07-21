#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:a
s/\<char\>([[:space:]]+)\<signed\>/\signed\1char/g
s/\<char\>([[:space:]]+)\<(const|volatile|restrict|_Atomic)\>/\2\1char/g
s/\<signed\>([[:space:]]+)\<(const|volatile|restrict|_Atomic)\>/\2\1signed/g
t a
s/\<signed\>([[:space:]]+\<char\>)/\1/g
' "$file"