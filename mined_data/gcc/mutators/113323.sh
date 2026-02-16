#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

typedef_info=$(grep -n -E -m 1 '^\s*typedef.*__vector_size__' "$file")
if [[ -z "$typedef_info" ]]; then
    exit 0
fi

typedef_ln=$(echo "$typedef_info" | cut -d: -f1)
typedef_line=$(echo "$typedef_info" | cut -d: -f2-)

base_type=$(echo "$typedef_line" | sed -E 's/^\s*typedef\s+(.*)\s+__attribute__.*/\1/' | xargs)
vec_type=$(echo "$typedef_line" | sed -E 's/.*\)\s*(\w+)\s*;.*/\1/')

if [[ -z "$base_type" || -z "$vec_type" ]]; then
    exit 1
fi

var_decl_pattern="^\s*${vec_type}\s+\w+\s*,\s*\w+\s*;"
var_decl_info=$(tail -n +$typedef_ln "$file" | grep -n -E -m 1 "$var_decl_pattern")

if [[ -z "$var_decl_info" ]]; then
    exit 0
fi

var_decl_rel_ln=$(echo "$var_decl_info" | cut -d: -f1)
var_decl_ln=$((typedef_ln + var_decl_rel_ln - 1))
var_decl_line=$(echo "$var_decl_info" | cut -d: -f2-)

if [[ "$var_decl_ln" -gt $((typedef_ln + 1)) ]]; then
    intervening_lines=$(sed -n "$((typedef_ln + 1)),$((var_decl_ln - 1))p" "$file")
    if echo "$intervening_lines" | grep -q -v -E '^\s*$' ; then
        exit 0
    fi
fi

vars_part=$(echo "$var_decl_line" | sed -E "s/^\s*${vec_type}\s+(.*);/\1/")
var1=$(echo "$vars_part" | sed -E 's/\s*,.*//' | xargs)
var2=$(echo "$vars_part" | sed -E 's/.*,\s*//' | xargs)

if [[ -z "$var1" || -z "$var2" ]]; then
    exit 1
fi

sed -i -E \
    -e "/^\s*typedef\s+.*__attribute__\(\(__vector_size__.*\)\)\s*${vec_type}\s*;/d" \
    -e "s/^\s*${vec_type}\s+${var1}\s*,\s*${var2}\s*;.*/${base_type} a, b;/" \
    -e "s/\b${var1}\b\s*=\s*\b${var2}\b/a = b/g" \
    "$file"