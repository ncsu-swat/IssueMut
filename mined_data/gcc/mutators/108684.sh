#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Block 1: Handle multi-line macros defined with #define
/^[[:space:]]*#define/ {
    :m_loop
    /\\$/ {
        $! {
            N
            b m_loop
        }
    }
    /(__asm__|asm)[[:space:]]*\(([^:]*:){3}[^)]*"\<memory\>"/!b

    /:[[:space:]]*[^:[:space:]\n][^:]*:[[:space:]]*:/ {
        s/(__asm__|asm)[[:space:]]+volatile/\1/
        b
    }

    /(__asm__|asm)[[:space:]]+volatile/! s/(__asm__|asm)/& volatile/
    b
}

# Block 2: Handle regular (potentially multi-line) asm statements
/(__asm__|asm)[[:space:]]*\(/ {
    :s_loop
    /\);/! {
        $! {
            N
            b s_loop
        }
    }
    /\(([^:]*:){3}[^)]*"\<memory\>"/!b

    /:[[:space:]]*[^:[:space:]\n][^:]*:[[:space:]]*:/ {
        s/(__asm__|asm)[[:space:]]+volatile/\1/
        b
    }

    /(__asm__|asm)[[:space:]]+volatile/! s/(__asm__|asm)/& volatile/
}
' "$file"