#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Select an if statement containing a variable
ifs=$(grep -oE "if \([a-zA-Z_][a-zA-Z0-9_]*\)" "$file" | \
sed -E "s/if \(([a-zA-Z_][a-zA-Z0-9_]*)\)/\1/")

if [ -z "$ifs" ]; then
  echo "No matching patterns found."
  exit 0
fi

varName=$(echo "$ifs" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Find declaration for that variable and save its line number + what the variable equals to
declars=$(grep -noE "[a-zA-Z_][a-zA-Z0-9_]* $varName = [^;]*;" "$file" | \
sed -E "s/[a-zA-Z_][a-zA-Z0-9_]* $varName = ([^;]*);/\1/")

if [ -z "$declars" ]; then
  echo "No matching patterns found."
  exit 0
fi

declar=$(echo "$declars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
declarLine=$(echo "$declar" | cut -d: -f1)
equivalent=$(echo "$declar" | cut -d: -f2)

# Delete the declaration line 
sed -i -E "$declarLine s/[a-zA-Z_][a-zA-Z0-9_]* $varName = [^;]*;//" "$file"
# Replace the variable with what it's equal to every time it appears
sed -i -E "s/([^a-zA-Z0-9_])$varName([^a-zA-Z0-9_])/\1$equivalent\2/g" "$file"