#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# extract macro definitions
matches=$(grep -oE '#define [a-zA-Z_][a-zA-Z0-9_]*\(([a-zA-Z_][a-zA-Z0-9_]*),?.*\)' "$file" | \
sed -E 's/#define [a-zA-Z_][a-zA-Z0-9_]*\(([a-zA-Z_][a-zA-Z0-9_]*),?.*\)/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
#   echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
random_picked_param=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# extract macro definitions
int8_t_matches=$(grep -noE 'int8_t' "$file")

# If no matches are found, exit
if [ -z "$int8_t_matches" ]; then
#   echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
random_matches=$(echo "$int8_t_matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$random_matches" | cut -d':' -f1)
sed -i -E "${line}s/int8_t/$random_picked_param/" "$file"