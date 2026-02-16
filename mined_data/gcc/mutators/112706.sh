#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
  -e 's/\([[:space:]]*([^[:space:]]+)[[:space:]]*-[[:space:]]*([^[:space:]]+)[[:space:]]*\)[[:space:]]*(==|!=)[[:space:]]*0/\1 \3 \2/g' \
  -e 's/0[[:space:]]*(==|!=)[[:space:]]*\([[:space:]]*([^[:space:]]+)[[:space:]]*-[[:space:]]*([^[:space:]]+)[[:space:]]*\)/\2 \1 \3/g' \
  -e 's/([^[:space:]]+)[[:space:]]*-[[:space:]]*([^[:space:]]+)[[:space:]]*(==|!=)[[:space:]]*0/\1 \3 \2/g' \
  -e 's/0[[:space:]]*(==|!=)[[:space:]]*([^[:space:]]+)[[:space:]]*-[[:space:]]*([^[:space:]]+)/\2 \1 \3/g' \
  "$file"