#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\([[:space:]]*unsigned[^)]*\)[[:space:]]*([^&]*)[[:space:]]*(&[[:space:]]*~[[:space:]]*[0-9a-fA-FxX]+)U([lL]*)/\1\2\3/g' "$file"