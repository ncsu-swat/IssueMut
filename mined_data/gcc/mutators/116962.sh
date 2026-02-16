#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '/__attribute__\s*\(\(.*\bnaked\b.*\)\)/{ /no_stack_protector/! s/\bnaked\b/&, no_stack_protector/g }' "$file"