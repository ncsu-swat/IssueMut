#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
  -e 's/^(.*)(\b(long long|long|short)\b)([[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*=[[:space:]]*)\([[:space:]]*\3[[:space:]]*\)[[:space:]]*(.*)/\1unsigned \2\4\5/' \
  -e 's/^(.*)(\bint\b)([[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*=[[:space:]]*)\([[:space:]]*\2[[:space:]]*\)[[:space:]]*(.*)/\1unsigned\3\4/' \
  "$file"