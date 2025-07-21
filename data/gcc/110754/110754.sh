#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/\[\[gnu::assume/ {
    :loop
    s/\(\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*&\s*0\s*\)/0/g
    s/\(\s*0\s*&\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\)/0/g
    t loop
}
' "$file"