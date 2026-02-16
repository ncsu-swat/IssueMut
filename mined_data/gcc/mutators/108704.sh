#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^\s*[^;=]+\s*=\s*\{/ {
    :a
    /};/! {
        $! {
            N
            ba
        }
    }
    s/\n/\x07/g
    s/\s*=\s*\{.*};/;/
    s/\x07/\n/g
}
' "$file"