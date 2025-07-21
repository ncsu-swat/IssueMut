#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E -e '
:a
s/\b_Atomic\s+//g
s/atomic_store\s*\(\s*&\s*([^,]+)\s*,\s*(.*)\s*\)/\1 = \2/
/^\s*#include <stdatomic.h>\s*$/ {
    $d
    N
    /\n\s*$/d
    s/.*\n//
    ba
}
' "$file"