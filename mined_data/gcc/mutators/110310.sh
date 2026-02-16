#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

perl -i -pe 's/(\[\s*|#define\s+\w+\s+|\s*[<>]=?\s*)(\d+)/$1 . int($2\/2)/ge' "$file"