#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -e 's/vbool64_t/vbool4_t/g' \
       -e 's/vfloat32m4_t/vfloat16m2_t/g' \
       -e 's/vuint64m8_t/vuint8m1_t/g' \
       -e 's/vint32mf2_t/vint64m1_t/g' "$file"