#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
  $!N
  /^([[:space:]]*).*(\+=|-=|\*=|%=|\/=|&=|\|=|\^=|<<=|>>=).*;[[:space:]]*\n/ {
    /\n[[:space:]]*(asm volatile|\})/! {
      s/^([[:space:]]*)(.*)\n(.*)$/\1\2\n\1asm volatile ("" ::: "memory");\n\3/
    }
  }
  P
  D
' "$file"