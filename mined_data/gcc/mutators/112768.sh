#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"
tmp_file=$(mktemp)

# Use Basic Regular Expressions (BRE) for better portability instead of ERE (-E).
# In BRE, parentheses are literals, which simplifies the expression for matching `((...))`.
# The pattern matches the attribute and any preceding whitespace, then removes it.
sed 's/[[:space:]]*__attribute__[[:space:]]*(([[:space:]]*no_btf_type_info[[:space:]]*))//g' "$file" > "$tmp_file" && mv "$tmp_file" "$file"