#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

OPERATORS="<<|>>|&&|\|\||==|!=|<=|>=|<|>|\+|-|\*|\/|%|&|\^|\|"

sed -i -E \
  -e "s/\(\(([^\(\)]+)\)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^\)]*\))\)([[:space:]]*($OPERATORS)[[:space:]]*)/(\3)\4/g" \
  -e "s/([[:space:]]*($OPERATORS)[[:space:]]*)\(\(([^\(\)]+)\)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^\)]*\))\)/\1(\4)/g" \
  -e "s/\(([^\(\)]+)\)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^\)]*\))([[:space:]]*($OPERATORS)[[:space:]]*)/\2\3/g" \
  -e "s/([[:space:]]*($OPERATORS)[[:space:]]*)\(([^\(\)]+)\)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^\)]*\))/\1\4/g" \
  "$file"