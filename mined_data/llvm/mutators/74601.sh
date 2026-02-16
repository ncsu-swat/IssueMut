#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Read in the entire struct declaration and save it as one line
structWhole=$(grep -zoE "typedef struct \{[^}]*\} [a-zA-Z_][a-zA-Z0-9_]*;" "$file" | \
tr '\0' '\n' | tr -d '\n') 

if [ -z "$structWhole" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Choose a random struct
struct=$(echo "$structWhole" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')


# Find a variable declaration inside struct
matches=$(echo "$struct" | grep -oE "[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*;" | \
sed -E "s/([a-zA-Z_][a-zA-Z0-9_]*) ([a-zA-Z_][a-zA-Z0-9_]*);/\1:\2/")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Choose a random variable, save its type and name
rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
typeName=$(echo "$rand_match" | cut -d: -f1)
varName=$(echo "$rand_match" | cut -d: -f2)

structName=$(echo "$struct" | grep -oE "\} [a-zA-Z_][a-zA-Z0-9_]*;" | sed -E "s/\} ([a-zA-Z_][a-zA-Z0-9_]*);/\1/")
if [ -z "$structName" ]; then
  echo "No matching patterns found."
  exit 0
fi


# Find a function header that uses the same variable type as the parameter
matches2=$(grep -noE "[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*$typeName [a-zA-Z_][a-zA-Z0-9_]*.*\)" "$file")
if [ -z "$matches2" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Select a random header, replace the variable type with the struct name
rand_match2=$(echo "$matches2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
line=$(echo "$rand_match2" | cut -d: -f1)

sed -i -E "${line} s/$typeName/$structName/" "$file"


# Find another function that uses the same type, save the function name
matches3=$(grep -oE "[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*$typeName [a-zA-Z_][a-zA-Z0-9_]*.*\)" "$file" | \
sed -E "s/[a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\(.*$typeName [a-zA-Z_][a-zA-Z0-9_]*.*\)/\1/")
if [ -z "$matches3" ]; then
  echo "No matching patterns found."
  exit 0
fi

funcName=$(echo "$matches3" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# When the function is called, add the variable after the previous argument
sed -i -E "s/$funcName\(([a-zA-Z_][a-zA-Z0-9_]*)\);/$funcName\(\1\.$varName\);/" "$file"
