#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
  -e 's/^(.*[{])\s*return\s+__builtin_popcount\s*\(\s*\(int\)\s*__builtin_bswap16\s*\(([^)]*)\)\s*\)\s*;\s*([}].*)$/\1\
  int temp = __builtin_bswap16(\2);\
  return __builtin_popcount(temp);\
\3/' \
  -e 's/^(\s*)return\s+__builtin_popcount\s*\(\s*\(int\)\s*__builtin_bswap16\s*\(([^)]*)\)\s*\)\s*;(.*)$/\1int temp = __builtin_bswap16(\2);\
\1return __builtin_popcount(temp);\3/' \
  "$file"