#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"
tmpfile=$(mktemp)
trap 'rm -f "$tmpfile"' EXIT

awk '
/^[[:space:]]*#(if|ifdef|ifndef)/ {
    depth++
    if (depth > 1 && skip[depth - 1]) {
        skip[depth] = 1
    } else {
        skip[depth] = 0
    }
    next
}

/^[[:space:]]*#(else|elif)/ {
    if (depth > 0) {
        skip[depth] = 1
    }
    next
}

/^[[:space:]]*#endif/ {
    if (depth > 0) {
        delete skip[depth]
        depth--
    }
    next
}

{
    if (depth == 0 || !skip[depth]) {
        print
    }
}
' "$file" > "$tmpfile" && mv "$tmpfile" "$file"