#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E '
  :a; N; $!ba;
  :loop
  s/(^|\n)([ \t]*)__MEMCPY_PTR__:([a-zA-Z_][a-zA-Z0-9_]*):([a-zA-Z_][a-zA-Z0-9_]*)\n\2\3->([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*\4->\5;[ \t]*/\1\2__MEMCPY_PTR__:\3:\4/
  t loop
  s/(^|\n)([ \t]*)([a-zA-Z_][a-zA-Z0-9_]*)->([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*([a-zA-Z_][a-zA-Z0-9_]*)->\4;[ \t]*\n\2\3->([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*\5->\6;[ \t]*/\1\2__MEMCPY_PTR__:\3:\5/
  t loop
  s/(^|\n)([ \t]*)__MEMCPY_DOT__:([a-zA-Z_][a-zA-Z0-9_]*):([a-zA-Z_][a-zA-Z0-9_]*)\n\2\3\.([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*\4\.\5;[ \t]*/\1\2__MEMCPY_DOT__:\3:\4/
  t loop
  s/(^|\n)([ \t]*)([a-zA-Z_][a-zA-Z0-9_]*)\.([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*([a-zA-Z_][a-zA-Z0-9_]*)\.\4;[ \t]*\n\2\3\.([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*=[ \t]*\5\.\6;[ \t]*/\1\2__MEMCPY_DOT__:\3:\5/
  t loop
  s/^[ \t]*__MEMCPY_PTR__:([a-zA-Z_][a-zA-Z0-9_]*):([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*$/memcpy(\1, \2, sizeof(*\1));/mg
  s/^[ \t]*__MEMCPY_DOT__:([a-zA-Z_][a-zA-Z0-9_]*):([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*$/memcpy(\&\1, \&\2, sizeof(\1));/mg
' "$file"