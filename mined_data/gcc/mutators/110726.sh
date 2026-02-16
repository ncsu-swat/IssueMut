#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
    :a; N; $!ba;

    s#(\([[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*==[[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*\))[[:space:]]*\?[[:space:]]*\([[:space:]]*(\2|\3)[[:space:]]*\|[[:space:]]*1[[:space:]]*\)[[:space:]]*:[[:space:]]*(\([[:space:]]*(\2[[:space:]]*\&[[:space:]]*\3|\3[[:space:]]*\&[[:space:]]*\2)[[:space:]]*\))#\5 | \1#g;

    s#(\([[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*==[[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*\))[[:space:]]*\?[[:space:]]*\([[:space:]]*(\2|\3)[[:space:]]*\|[[:space:]]*1[[:space:]]*\)[[:space:]]*:[[:space:]]*(\2|\3)\b#\5 | \1#g;

    s#(\([[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*==[[:space:]]*(\b[a-zA-Z0-9_]+\b)[[:space:]]*\))[[:space:]]*\?[[:space:]]*\([[:space:]]*((\2|\3)[[:space:]]*\&[[:space:]]*1|\2[[:space:]]*\&[[:space:]]*\3|\3[[:space:]]*\&[[:space:]]*\2)[[:space:]]*\)[[:space:]]*:[[:space:]]*0\b#(\2 | \3) \& \1#g;
' "$file"