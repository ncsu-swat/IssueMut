#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi
file="$1"
sed -i -E '
# Skip function pointers like "int (*p)()"
/\([[:space:]]*\*/b

# If volatile is present, remove it and skip to the next line.
s/(\*+[[:space:]]*)\bvolatile\b([[:space:]]+)/\1/g; t

# If volatile was not present, add it.
s/((^|[,;({])[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*([[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*)*)?)([[:space:]]*\*+)[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)/\1\5 volatile \6/g
' "$file"