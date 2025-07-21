#!/bin/bash

if [ $# -ne 2 ]; then 
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/^(static +[a-zA-Z_][a-zA-Z0-9_]* +[a-zA-Z_][a-zA-Z0-9_]*)\([a-zA-Z_][a-zA-Z0-9_]* *\* *[a-zA-Z_][a-zA-Z0-9_]*\) *;/\1();/' "$file"
sed -i -E 's/^([a-zA-Z_][a-zA-Z0-9_]* +[a-zA-Z_][a-zA-Z0-9_]*)\(([a-zA-Z_][a-zA-Z0-9_]*) *\* *([a-zA-Z_][a-zA-Z0-9_]*)\) *\{/\1(\3)\
\2 *\3;\
{/' "$file"
