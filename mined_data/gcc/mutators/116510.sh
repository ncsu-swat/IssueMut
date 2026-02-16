#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -z -E 's/switch[[:space:]]*\([[:space:]]*\([[:space:]]*int[[:space:]]*\)[[:space:]]*\([[:space:]]*unsigned[[:space:]]+char[[:space:]]*\)/&/g; t; s/(switch[[:space:]]*\()([[:space:]]*\([[:space:]]*unsigned[[:space:]]+char[[:space:]]*\))/\1(int)\2/g' "$file"