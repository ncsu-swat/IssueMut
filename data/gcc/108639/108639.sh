#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
  -e 's/([a-zA-Z_][a-zA-Z0-9_>.-]*)[ \t]*=[ \t]*\1[ \t]*<<[ \t]*\1([^a-zA-Z0-9_])/\1 = \1 << (int)\1\2/g' \
  -e 's/([a-zA-Z_][a-zA-Z0-9_>.-]*)[ \t]*([+*/%&|^-])=[ \t]*\1[ \t]*<<[ \t]*\1([^a-zA-Z0-9_])/\1 \2= \1 << (int)\1\3/g' \
  -e 's/([a-zA-Z_][a-zA-Z0-9_>.-]*)[ \t]*<<=[ \t]*\1([^a-zA-Z0-9_])/\1 <<= (int)\1\2/g' \
  "$file"