#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^\s*($|\/\/|\/\*|#)/b
/\b(void|char|short|int|long|float|double|signed|unsigned|struct|union|enum)\b/ {
    /^[^=]*\b[a-zA-Z_][a-zA-Z0-9_]*\s*\(/b
    /\b[a-zA-Z_][a-zA-Z0-9_]*\s*\[/b
    /^\s*(typedef\s+)?(struct|union|enum)[^;]*\{/b
    /\bvolatile\b/b

    /^\s*(extern|static|typedef)/ {
        s/^\s*(extern|static|typedef)\s+/&volatile /
        b
    }

    s/^(\s*)/\1volatile /
}
' "$file"