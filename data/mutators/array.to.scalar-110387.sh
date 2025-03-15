
#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# find all the array variables
matches=$(grep -oE '[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\[4\];' "$file" | \
sed -E 's/[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\[4\];/\1/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
array_var=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

sed -i -E "s/$array_var\[0\]/a/g; s/$array_var\[1\]/b/g; s/$array_var\[2\]/c/g; s/$array_var\[3\]/d/g; s/$array_var\[4\]/a, b, c, d/g" "$file"
