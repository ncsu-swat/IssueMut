#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E ':a; N; $!ba; s/(\{)(\s*[^{};]+;\s*)(\})/\1\3/g' "$file"