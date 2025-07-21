#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/\(.*\)\s*\{$/ {
    h
    s/.*\b([a-zA-Z_][a-zA-Z0-9_]+)\s*\).*/\1/
    t check_void
    b

:check_void
    /^void$/b
    x

:loop
    n
    /\[[^]]+\];/ {
        G
        s/\[[^]]+\](.*)\n(.*)/[\2]\1/
    }
    /};/! b loop
}
' "$file"