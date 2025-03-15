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
matches=$(grep -noE '__attribute__(.*),\s*target\s*\([^)]*\)(.*)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__(.*),\s*target\s*\([^)]*\)(.*)/__attribute__\1\2/" "$file"
fi

#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '__attribute__\s*\(\s*\(\s*target\s*\([^)]*\)\s*\)\s*\)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__\s*\(\s*\(\s*target\s*\([^)]*\)\s*\)\s*\)//" "$file"
fi

#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '__attribute__\s*\(\s*\(\s*target\s*\([^)]*\)\s*,(.*)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__\s*\(\s*\(\s*target\s*\([^)]*\)\s*,(.*)/__attribute__\(\(\1/" "$file"
fi

#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '__attribute__(.*),\s*__target__\s*\([^)]*\)(.*)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__(.*),\s*__target__\s*\([^)]*\)(.*)/__attribute__\1\2/" "$file"
fi

#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '__attribute__\s*\(\s*\(\s*__target__\s*\([^)]*\)\s*\)\s*\)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__\s*\(\s*\(\s*__target__\s*\([^)]*\)\s*\)\s*\)//" "$file"
fi

#### Randomly pick one
# Find all occurrences
matches=$(grep -noE '__attribute__\s*\(\s*\(\s*__target__\s*\([^)]*\)\s*,(.*)' "$file")

if [ -n "$matches" ]; then
  # Convert matches to an array and randomly pick one
  random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  
  # Extract line and column from the random match
  line=$(echo "$random_match" | cut -d: -f1)
  
  sed -i -E "${line}s/__attribute__\s*\(\s*\(\s*__target__\s*\([^)]*\)\s*,(.*)/__attribute__\(\(\1/" "$file"
fi