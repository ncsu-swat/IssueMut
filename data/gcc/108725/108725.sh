#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E -f - "$file" <<'EOF'
# Read the whole file into pattern space to handle multiline patterns
:a
N
$!ba

# Rule for pointer types: e.g., T *v1; T *v2; v1=i1; v2=i2; -> T *v1=i1, *v2=i2;
s/(^|\n)([[:space:]]*)([^;\n*]+[[:space:]]*)(\*) *([a-zA-Z_][a-zA-Z0-9_]*);\n\2\3\4 *([a-zA-Z_][a-zA-Z0-9_]*);\n\2\5 = ([^;\n]*);\n\2\6 = ([^;\n]*);/\1\2\3\4\5 = \7, \4\6 = \8;/g

# Rule for non-pointer types: e.g., T v1; T v2; v1=i1; v2=i2; -> T v1=i1, v2=i2;
s/(^|\n)([[:space:]]*)([^;\n*]+) ([a-zA-Z_][a-zA-Z0-9_]*);\n\2\3 ([a-zA-Z_][a-zA-Z0-9_]*);\n\2\4 = ([^;\n]*);\n\2\5 = ([^;\n]*);/\1\2\3 \4 = \6, \5 = \7;/g
EOF