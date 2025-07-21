#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E -z 's#\{(\s*typedef\s+[^;]*int[^;]*;\s*const\s+\w+\s+C\s*=\s*\{[^}]+\};\s*[a-zA-Z0-9_ \t]+\s+([a-zA-Z0-9_]+)\s*=\s*([^;]*);\s*[a-zA-Z0-9_ \t]+\s+([a-zA-Z0-9_]+)\s*=\s*([^;]*);\s*return[^;]*\b\2\b[^>]*>\s*[^;]*\b\4\b[^;]*;\s*)\}# { return ~(\3 <= \5); }#g' "$file"