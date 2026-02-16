#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(\b_mm(512|256)?_maskz_cvtne2ps_pbh\s*\([^,]+,\s*)([^,]+)(\s*,\s*)(.*)\)/\1\5\4\3)/g' "$file"