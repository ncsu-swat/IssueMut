#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E -f - "$file" <<'SED_SCRIPT'
/^\s*case\s+.*:/ {
    /\.\.\./ {
        s/(case\s+)(.*)\s+\.\.\.\s+([^:]+)(:.*)/case -(\3) ... -(\2)\4/
        b simplify
    }

    s/(case\s+)([^:]+)(:.*)/case -(\2)\3/

    :simplify
    :loop
    s/-\s*\(\s*-([^)]*)\s*\)/\1/g
    t loop

    s/-\s*\(([^)]*)\)/-\1/g
    t loop
}
SED_SCRIPT