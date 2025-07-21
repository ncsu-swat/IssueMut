#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i 's/(\(void\)__builtin_cpu_supports("f16c"));/\1;  (void)__builtin_cpu_supports("avx512fp16");/' "$file"