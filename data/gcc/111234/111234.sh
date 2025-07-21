#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

sed -i -E '
/v(int|uint|float)[0-9]+m(f)?[0-9]+_t/ {
    /^[[:space:]]*typedef/b
    /v(int|uint|float)[0-9]+m(f)?[0-9]+_t[[:space:]]*\**[[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\(/b
    /volatile/b
    s/^([[:space:]]*)(v(int|uint|float)(8|16|64)m(f)?[0-9]+_t)/\1volatile \2/
}
' "$1"