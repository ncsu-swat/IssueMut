#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# s/([a-zA-Z_][a-zA-Z0-9_]*)\((struct [a-zA-Z_][a-zA-Z0-9_]*) \*([a-zA-Z_][a-zA-Z0-9_]*)\)/\1(\2 \3)/

# Find all the unsigned long variables
matches=$(grep -noE '([a-zA-Z_][a-zA-Z0-9_]*)\((struct [a-zA-Z_][a-zA-Z0-9_]*) \*([a-zA-Z_][a-zA-Z0-9_]*)\)' "$file" | \
sed -E 's/([a-zA-Z_][a-zA-Z0-9_]*)\((struct [a-zA-Z_][a-zA-Z0-9_]*) \*([a-zA-Z_][a-zA-Z0-9_]*)\)/\1:\3/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  # echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)
function_name=$(echo "$random_match" | cut -d: -f2)
parameter_name=$(echo "$random_match" | cut -d: -f3)

sed -i -E "s/$function_name\(struct(.*) \*([a-zA-Z_][a-zA-Z0-9_]*)\)/$function_name(struct\1 \2)/" "$file"

sed -i -E "$line!s/$parameter_name->/$parameter_name./" "$file"

sed -i -E "$line!s/$function_name\((.*)\)/$function_name(*\1)/" "$file"
