#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(.*\breturn\s+)(\(_Bool\)\s*)?([^^\n]*[^^\n[:space:]])\s*\^\s*(\(_Bool\)\s*)?([^;\n]*[^;[:space:]])(\s*;.*)$/\1nand(nand(\5, nand(\3, \3)), nand(\3, nand(\5, \5)))\6/' "$file"