#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[ \t]*([a-zA-Z_][a-zA-Z0-9_]+):[ \t]*$/ {
    :loop
    $!N
    s/^([ \t]*)([a-zA-Z_][a-zA-Z0-9_]+):[ \t]*\n(.*?)[ \t]*if[ \t]*\((.*)\)[ \t]*\n?[ \t]*goto[ \t]+\2;[ \t]*(\n?)/\1do {\n\3\1} while (\4);\5/
    t
    b loop
}
' "$file"