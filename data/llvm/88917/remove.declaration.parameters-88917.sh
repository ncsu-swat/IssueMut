#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Save a random function definition's type and name
definitions=$(grep -oE "[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*\) \{" "$file" | \
sed -E "s/([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*)\(.*\) \{/\1/")
if [ -z "$definitions" ]; then
  echo "No matching patterns found."
  exit 0
fi
funcName=$(echo "$definitions" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Find a matching declaration
declarations=$(grep -noE "$funcName\([^\{]*\);" "$file")

# If a declaration is found, modify the line to get rid of the parameter
if [ -n "$declarations" ]; then
  declaration=$(echo "$declarations" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  declar_line=$(echo "$funcName" | cut -d: -f1)
  sed -i -E "s/($funcName)\(.*\);/\1\(\);/" "$file"
fi