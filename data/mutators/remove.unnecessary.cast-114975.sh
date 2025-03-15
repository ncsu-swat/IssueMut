#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E "s/\(\s*(int|short|long|long\s+long|unsigned\s+int|unsigned\s+short|unsigned\s+long|unsigned\s+long\s+long|int8_t|uint8_t|int16_t|uint16_t|int32_t|uint32_t|int64_t|uint64_t)\s*\)//g" "$file"
