#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/vector (.*) long long/vector \1 __int128/' "$file"
sed -i -E 's/__builtin_pack_vector_longlong/__builtin_pack_vector_int128/' "$file"
