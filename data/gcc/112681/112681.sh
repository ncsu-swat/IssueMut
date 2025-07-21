#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
:a;
N;
$!ba;

s!([ \t]*)for[ \t\n]*\([^;]*;[ \t\n]*([a-zA-Z_][a-zA-Z0-9_]*)[ \t\n]*<[ \t\n]*([^;]+);[ \t\n]*[^)]+\)[ \t\n]*\{[ \t\n]*if[ \t\n]*\(([^[]+)\[\2\][ \t\n]*\!=[ \t\n]*([^[]+)\[\2\]\)[ \t\n]*(\{[ \t\n]*)?return[ \t]+0;[ \t\n]*(\})?[ \t\n]*\}[ \t\n]*return[ \t]+1;!\1return __builtin_memcmp(\4, \5, \3) == 0;!g

s!([ \t]*)for[ \t\n]*\([^;]*;[ \t\n]*([a-zA-Z_][a-zA-Z0-9_]*)[ \t\n]*<[ \t\n]*([^;]+);[ \t\n]*[^)]+\)[ \t\n]*\{[ \t\n]*if[ \t\n]*\(([^[]+)\[\2\][ \t\n]*\!=[ \t\n]*([^[]+)\[\2\]\)[ \t\n]*(\{[ \t\n]*)?return[ \t]+1;[ \t\n]*(\})?[ \t\n]*\}[ \t\n]*return[ \t]+0;!\1return __builtin_memcmp(\4, \5, \3) \!= 0;!g
' "$file"