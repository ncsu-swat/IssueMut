#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2


#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '([a-zA-Z_][a-zA-Z0-9_]*)\(([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, )*([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*)\)' "$file" \
| sed -E 's/([a-zA-Z_][a-zA-Z0-9_]*)\(([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, )*([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*)\)/\4/')

echo "$matches"

if [ -z "$matches" ]; then
#   echo "No matching patterns found."
  exit 1
fi

# Randomly select one of the matches
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

echo "$random_match"

# Extract line and column from the random match
line=$(echo "$random_match" | cut -d: -f1)
parameter_name=$(echo "$random_match" | cut -d: -f2)

echo "$line"
echo "$parameter_name"


sed -i -E "${line}s/([a-zA-Z_][a-zA-Z0-9_]*)\(([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, )*([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*)\)/__attribute__((const)) \1(\2\3 \4)/" "$file"

sed -i -E "1i #pragma omp declare simd notinbranch uniform(${parameter_name})" "$file"

sed -i -E "/[a-zA-Z_][a-zA-Z0-9_]*\(([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, )*[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\) \{/a #pragma omp simd" "$file"