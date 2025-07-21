#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E 's#([[:space:]]*)\*([[:space:]]*)(0(\.0*)?([fFlL])?\b)#\1/\2\3#g' "$file"