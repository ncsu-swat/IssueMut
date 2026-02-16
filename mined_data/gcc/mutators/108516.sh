#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/\bunsigned(([ \t]+(int|short|long|char)\b)+)?[ \t]+([[:alpha:]_][[:alnum:]_]*)[ \t]*:[ \t]*8\b/unsigned char \4/g' "$file"