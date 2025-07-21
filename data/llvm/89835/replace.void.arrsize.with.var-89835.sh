#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# find (void)(int[num]){}; and save num
matches1=$(grep -noE "\(void\)\([a-zA-Z_][a-zA-Z0-9_]*\[[0-9]+\]\)\{" "$file" | \
sed -E "s/\(void\)\([a-zA-Z_][a-zA-Z0-9_]*\[([0-9]+)\]\)\{/\1/")
if [ -z "$matches1" ]; then
    echo "No matching patterns found."
    exit 0
fi
rand_match1=$(echo "$matches1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match1" | cut -d: -f1)
value=$(echo "$rand_match1" | cut -d: -f2)

# Find an int variable that is initialized to num, save the variable name
matches2=$(grep -oE "int [a-zA-Z_][a-zA-Z0-9_]* =" "$file" | \
sed -E "s/int ([a-zA-Z_][a-zA-Z0-9_]*) =/\1/")
if [ -z "$matches2" ]; then
    echo "No matching patterns found."
    exit 0
fi
var_name=$(echo "$matches2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Replace the number with the variable name
sed -i -E "${line} s/$value/$var_name/" "$file"