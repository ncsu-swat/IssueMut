#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find the pattern int a, and save the variable name
intVars=$(grep -oE "int [a-zA-Z_][a-zA-Z0-9_]*," "$file" | \
sed -E 's/int ([a-zA-Z_][a-zA-Z0-9_]*),/\1/')

if [ -z "$intVars" ]; then
  echo "No matching patterns found."
  exit 0
fi
echo "$intVars"

intVar=$(echo "$intVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Find the pattern var = var
equals=$(grep -noE "[a-zA-Z_][a-zA-Z0-9_]* = [a-zA-Z_][a-zA-Z0-9_]*;" "$file")

if [ -z "$equals" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Find a random match
random_match=$(echo "$equals" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$random_match" | cut -d: -f1)

# Insert a; in the next line
sed -i -E "${line} a\\
${intVar};" "$file"