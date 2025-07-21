#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

# The file name
file="$1" 
SEED="$2"

added_params="b, i, j, k, l, m"

added_params_types="_Bool b, char i, short j, int k, float l, double m"

sed -i -E "s/\.\.\.\)\s*\{/${added_params_types}) {/" "$file"

va_list_matches=$(grep -n -E "(va_list)" "$file")

random_va_list=$(echo "$va_list_matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() < 1/NR) line=$0} END {print line}')

keyword=$(echo "$random_va_list" | grep -o -P "va_list\s+\K[a-zA-Z_][a-zA-Z0-9_]*" "$file")

sed -i "s/${keyword}/${added_params}/" "$file"

line_number=$(echo "$random_va_list" | awk -F ":" '{print $1}')

sed -i -E "${line_number}d" "$file"

sed -i -E '/(va_start|va_end)/d' "$file"
