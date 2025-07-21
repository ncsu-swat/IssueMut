#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
  's/(\([[:space:]]*(unsigned[[:space:]]+long[[:space:]]+long|unsigned[[:space:]]+long|unsigned[[:space:]]+short|unsigned[[:space:]]+int|unsigned)[[:space:]]*\))[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)/\3/g' \
  "$file"