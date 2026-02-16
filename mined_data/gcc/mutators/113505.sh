#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

DECL_REGEX_SEARCH='^[[:space:]]*(.*[[:space:]]+)\b([a-zA-Z_][a-zA-Z0-9_]+)[[:space:]]*=[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]+[[:space:]]*\([[:space:]]*\))[[:space:]]*;'

subst_cmds=$(sed -n -E "s/${DECL_REGEX_SEARCH}/s#\\\\b\\2\\\\[#\\3[#g/p" "$file")

if [ -n "$subst_cmds" ]; then
    delete_cmd="\@${DECL_REGEX_SEARCH}@d"
    
    script=$(echo "$subst_cmds" | tr '\n' ';')
    
    full_script="${delete_cmd};${script}"
    
    sed -i -E "$full_script" "$file"
fi