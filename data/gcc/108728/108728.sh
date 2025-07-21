#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^([ \t]*)(.*)\s*=\s*(.*)\s*(>=|<=|==|!=|>|<)\s*([^;]+)\s*;$/{
  h
  s//\1if (__builtin_isunordered(\3, \5))\n\1  feraiseexcept(FE_INVALID);/
  x
  G
}
' "$file"