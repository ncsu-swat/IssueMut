#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Read in the entire struct declaration and save it as one line
structWhole=$(grep -zoE "struct [a-zA-Z_][a-zA-Z0-9_]* \{[^}]*\};" "$file" | \
tr '\0' '\n' | tr -d '\n') 

if [ -z "$structWhole" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Choose a random struct
struct=$(echo "$structWhole" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Find an int variable within struct declaration
intVars=$(echo "$struct" | grep -oE "int [a-zA-Z_][a-zA-Z0-9_]*;" | \
sed -E "s/int ([a-zA-Z_][a-zA-Z0-9_]*);/\1/")

if [ -z "$intVars" ]; then
  echo "No matching patterns found."
  exit 0
fi

intVar=$(echo "$intVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Remove array size and add __attribute__((__counted_by__(intVar)));
sed -i -E "s/([a-zA-Z_][a-zA-Z0-9_]*) \*([a-zA-Z_][a-zA-Z0-9_]*)\[[0-9]+\];/\1 \*\2\[\] __attribute__\(\(__counted_by__\(${intVar}\)\)\);/" "$file"