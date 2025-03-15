#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

#### Randomly pick one
# Find all occurrences of variable initialized with a function call
matches=$(grep -noE '[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*) = ([a-zA-Z_][a-zA-Z0-9_]*\(.*\));' "$file" | \
sed -E 's/[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*) = ([a-zA-Z_][a-zA-Z0-9_]*\(.*\));/\1:\2/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Convert matches to an array and randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
decl_line=$(echo "$random_match" | cut -d: -f1)
var=$(echo "$random_match" | cut -d: -f2)
function_call=$(echo "$random_match" | cut -d: -f3)

sed -i -E "${decl_line}s/[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*) = ([a-zA-Z_][a-zA-Z0-9_]*\(.*\));//" "$file"

sed -i -E "s/([^a-zA-Z0-9_])$var([^a-zA-Z0-9_])/\1$function_call\2/" "$file"
