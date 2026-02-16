#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find a random pointer declaration
pointers=$(grep -noE "long \*([a-zA-Z_][a-zA-Z0-9_]*) = \&([a-zA-Z_][a-zA-Z0-9_]*);" "$file" | \
sed -E "s/long \*([a-zA-Z_][a-zA-Z0-9_]*) = \&([a-zA-Z_][a-zA-Z0-9_]*);/\1:\2/")

if [ -z "$pointers" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Randomly pick a pointer declaration 
random_match1=$(echo "$pointers" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
pointerLine=$(echo "$random_match1" | cut -d: -f1)
pointerName=$(echo "$random_match1" | cut -d: -f2)
varName=$(echo "$random_match1" | cut -d: -f3)

# Delete the pointer declaration
sed -i -E "${pointerLine} s/long \*([a-zA-Z_][a-zA-Z0-9_]*) = \&([a-zA-Z_][a-zA-Z0-9_]*);//" "$file"

# Find a declaration of the chosen variable
longVars=$(grep -noE "long ${varName} = [0-9]+;" "$file" | \
sed -E "s/long ${varName} = ([0-9]+);/\1/")

if [ -z "$longVars" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Randomly pick a random declaration
random_match2=$(echo "$longVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
longLine=$(echo "$random_match2" | cut -d: -f1)

# Replace the variable name with the pointer name
sed -i -E "${longLine} s/long ${varName} = ([0-9]+);/long ${pointerName} = \1;/" "$file"

# Replace any reference to the pointer with the new variable
sed -i -E "s/([^a-zA-Z0-9_])\*${pointerName}([^a-zA-Z0-9_])/\1${pointerName}\2/g" "$file"



