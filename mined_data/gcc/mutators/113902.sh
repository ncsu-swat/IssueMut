#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

FLAG_VAR=$(sed -n -E 's/^[[:space:]]*}[[:space:]]*while[[:space:]]*\(([a-zA-Z_][a-zA-Z0-9_]*)\)[[:space:]]*;.*/\1/p' "$file" | head -1)

if [ -z "$FLAG_VAR" ]; then
    exit 0
fi

LABEL=$(echo "$FLAG_VAR" | sed -E 's/^(should|retry|reset)_//; s/search/search_again/; s/restart/restart_point/; s/outer/outer_loop_start/')
if [[ "$LABEL" == "$FLAG_VAR" ]]; then
    LABEL="lbl_$(echo "$FLAG_VAR" | cksum | cut -d' ' -f1)"
fi

sed -i -E '
:a; N; $!ba;

s/'"$FLAG_VAR"'[[:space:]]*=[[:space:]]*1;[[:space:]]*break;/goto '"$LABEL"';/g
s/[[:space:]]*if[[:space:]]*\([[:space:]]*'"$FLAG_VAR"'[[:space:]]*\)[[:space:]]*\{[[:space:]]*break;[[:space:]]*\}//g
s/[[:space:]]*if[[:space:]]*\([[:space:]]*'"$FLAG_VAR"'[[:space:]]*\)[[:space:]]*break[[:space:]]*;//g
s/([[:space:]]*)int[[:space:]]+'"$FLAG_VAR"'[[:space:]]*;[[:space:]]*do[[:space:]]*\{[[:space:]]*'"$FLAG_VAR"'[[:space:]]*=[[:space:]]*0[[:space:]]*;/\1'"$LABEL"':/g
s/[[:space:]]*\}[[:space:]]*while[[:space:]]*\([[:space:]]*'"$FLAG_VAR"'[[:space:]]*\)[[:space:]]*;[[:space:]]*//g
' "$file"