#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

if grep -q -w '__builtin_memmove' "$file"; then
    sed -i 's/\<__builtin_memmove\>/__builtin_memcpy/g' "$file"
else
    sed -i 's/\<__builtin_memcpy\>/__builtin_memmove/g' "$file"
fi