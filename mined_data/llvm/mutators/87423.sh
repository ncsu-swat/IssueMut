#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED="$2"

# 1. Find all matches (functions with preserve_most or preserve_all)
matches=$(grep -noE '__attribute__\(\(preserve_(most)\)\)' "$file")
if [ -z "$matches" ]; then
    echo "No matching patterns found."
    exit 0
fi

# 2. Randomly pick one match using awk 
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); n=0} {n++; lines[n]=$0} END {if(n>0) print lines[int(rand()*n)+1]}')

# 3. Extract the line number 
line_num=$(echo "$random_match" | cut -d: -f1)

# 4. Replace preserve_most or preserve_all with preserve_none on that line
sed -i "${line_num}s/preserve_most/preserve_none/" "$file"


