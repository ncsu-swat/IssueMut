#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# function header containing the type
matches=$(grep -noE "[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*, [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\) \{" "$file" | \
sed -E "s/[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*), [a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*), [a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\) \{/\1:\2:\3/")
# If no matches are found, exit
if [ -z "$matches" ]; then
#   echo "No matching patterns found."
  exit 1
fi


# randomly pick a header
params=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$params" | cut -d: -f1)
int=$(echo "$params" | cut -d: -f2)
double=$(echo "$params" | cut -d: -f3)
int2=$(echo "$params" | cut -d: -f4)


sed -i -E "s/__builtin_popcountg\($int\);//" "$file"

sed -i -E "${line} a\\
__builtin_popcountg\($int2\);" "$file"
sed -i -E "${line} a\\
__builtin_popcountg\($double\);" "$file"
sed -i -E "${line} a\\
__builtin_popcountg\($int, $int\);" "$file"
sed -i -E "${line} a\\
__builtin_popcountg\(\);" "$file"


