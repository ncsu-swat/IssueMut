#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file_to_process="$1"

sed -i -E 's/^([[:space:]]*)(.*[^[:space:]])\s*=\s*(.*?)\s*\?\s*(.*?)\s*:\s*(.*[^[:space:]])\s*;(.*)$/\1if (\3) { \2 = \4; } else { \2 = \5; }\6/' "$file_to_process"