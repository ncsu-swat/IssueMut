#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

def_start_line=$(sed -n '/^[[:space:]]*static[[:space:]]\+const.*=.*{/ {=; q}' "$file")

if [ -z "$def_start_line" ]; then
    exit 0
fi

def_end_line=$(sed -n "$def_start_line,\$ {/};/ {=; q}}" "$file")

if [ -z "$def_end_line" ]; then
    exit 1
fi

range="${def_start_line},${def_end_line}"

def_block=$(sed -n "${range}p" "$file")

arr_name=$(echo "$def_block" | head -n 1 | sed -E 's/.*\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\[.*$/\1/')
if [ -z "$arr_name" ]; then
    exit 1
fi

local_def_escaped=$(echo "$def_block" |
    sed -e 's/^[[:space:]]*static[[:space:]]*//' -e 's/^/    /' |
    sed -e 's/[\\/&]/\\&/g' -e 's/$/\\n/' |
    tr -d '\n' |
    sed 's/\\n$//'
)

sed_script="
${range}d

/\)[[:space:]]*\{/ {
    /^[[:space:]]*(if|for|while|switch|do|struct|enum|union)\b/! {
        :read_func_body
        h
        :balance_braces
        s/\{[^{}]*\}//g
        t balance_braces
        /\{/ {
            g
            \$!{
                N
                b read_func_body
            }
        }
        g
        /\b${arr_name}\b/ {
            s/\{/&\\
${local_def_escaped}/
        }
    }
}
"

sed -i -E -e "$sed_script" "$file"