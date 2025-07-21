#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Skip lines that are already if/for/while etc.
/^\s*(if|for|while|switch|return)\b/b

# Transform a function call with a ternary argument into an if-else block.
# Captures: 1=indent, 2=func+paren, 3=condition, 4=true_val, 5=false_val
s/^(\s*)([^(]+\()\s*([^?]+)\s*\?\s*([^:]+)\s*:\s*(.*)\s*\)\s*;/if (\3) {\n\1  \2\4);\n\1} else {\n\1  \2\5);\n\1}/
' "$file"