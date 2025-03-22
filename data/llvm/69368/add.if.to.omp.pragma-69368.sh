#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

intVars=$(grep -oE "int ([a-zA-Z_][a-zA-Z0-9_]*) .*;" "$file" | \
sed -E "s/int ([a-zA-Z_][a-zA-Z0-9_]*) .*;/\1/") 

if [ -z "$intVars" ]; then
  echo "No matching patterns found."
  exit 0
fi

intVar=$(echo "$intVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "s/#pragma omp teams distribute parallel for/#pragma omp teams distribute parallel for if \(${intVar} >= 2\)/" "$file"