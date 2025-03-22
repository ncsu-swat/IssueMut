#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Look for the main method and save the third parameter's name
mainMethod=$(grep -noE "int main\(.* char \*\*[a-zA-Z_][a-zA-Z0-9_]*\) \{" "$file" | \
sed -E "s/int main\(.* char \*\*([a-zA-Z_][a-zA-Z0-9_]*)\) \{/\1/") 

if [ -z "$mainMethod" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match=$(echo "$mainMethod" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$random_match" | cut -d: -f1)
envp=$(echo "$random_match" | cut -d: -f2)

# Remove the parameters in the main method
sed -i -E "${line} s/int main\(.* char \*\*[a-zA-Z_][a-zA-Z0-9_]*\) \{/int main\(\) \{/" "$file"

# Add extern char **environ; in the first line
sed -i -E '1 i\extern char \*\*environ;' "$file"

# Replace every envp with environ
sed -i -E "s/([^a-zA-Z0-9_])${envp}([^a-zA-Z0-9_])/\1environ\2/g" "$file"