#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E '$!N;s/^(.*\bfclose\b[[:blank:]]*\([[:blank:]]*([][*a-zA-Z0-9_>.-]+)[[:blank:]]*\).*)\n[[:blank:]]*\2[[:blank:]]*=[[:blank:]]*NULL[[:blank:]]*;.*$/\1/;P;D' "$file"