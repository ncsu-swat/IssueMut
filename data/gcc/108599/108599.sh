#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E ':a; s/(\*\s*\()([^()]*?)\bvolatile\b\s*([^)]*\))/\1\2\3/; ta' "$file"