#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[[:space:]]*if[[:space:]]*\(/{
    :gather
    /else[^{]*([;}])\s*$/!{
        $!{
            N
            b gather
        }
    }

    h

    s/\n/ /g
    s/[[:space:]]+/ /g
    s/^[[:space:]]+//
    s/[[:space:]]+$//

    s!^if \((.*)\) *\{? *(.*[^[:space:]]) *= *1 *;? *\}? *else *\{? *\2 *= *([^;]*[^;[:space:]]) *;? *\}?$!\2 = \1 ?: \3;!
    
    t reformat

    x
    b

:reformat
    x
    s/^([[:space:]]*).*/\1/
    G
    s/\n//
}' "$file"