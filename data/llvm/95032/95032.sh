#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(typedef\s+)?(struct|union)\s+(alignas\s*\([^)]+\))(\s+\w+)?(\s*\{)/\1\2\4\5 \3 /' "$file"