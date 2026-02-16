#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
    -e 's/\bunsigned long long\b/long long/g' \
    -e 's/\bunsigned long\b/long/g' \
    -e 's/\bunsigned short\b/short/g' \
    -e 's/\bunsigned char\b/signed char/g' \
    -e 's/\bunsigned int\b/int/g' \
    -e 's/\bunsigned\b/int/g' \
    "$file"