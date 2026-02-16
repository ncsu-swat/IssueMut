#!/bin/bash

VAR_NAMES=$(sed -n -E 's/^[[:space:]]*volatile[[:space:]]+.*\b([a-zA-Z_][a-zA-Z0-9_]*)\b[[:space:]]*=[[:space:]]*1[[:space:]]*;.*/\1/p' "$1")

if [ -z "$VAR_NAMES" ]; then
    exit 0
fi

SED_SCRIPT=""
for VAR_NAME in $VAR_NAMES; do
    SED_SCRIPT+="/^[[:space:]]*volatile[[:space:]]+.*\b${VAR_NAME}\b[[:space:]]*=[[:space:]]*1[[:space:]]*;/d;"
    SED_SCRIPT+="s/(\S+)[[:space:]]*-[=[[:space:]]*\b${VAR_NAME}\b/\1--/g;"
done

sed -i -E "$SED_SCRIPT" "$1"