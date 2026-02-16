#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(memcpy\([^,]+,\s*")(.*)([^"\\]|\\.)(".*)/\1\2\\0\4/' "$file"