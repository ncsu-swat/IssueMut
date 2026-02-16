#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/_mm256_andnot_si256\((.*),(.*)\)/\2 \& ~\1/' "$file"
sed -i -E 's/_mm256_testz_si256/__builtin_ia32_ptestz256/' "$file"
sed -i '1i typedef long long __m256i __attribute__ ((__vector_size__ (32)));\n' "$file"