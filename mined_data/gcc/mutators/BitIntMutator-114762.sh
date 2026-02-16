#!/bin/bash

# Check if a file is provided as the first argument
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <filename> <seed>"
  exit 1
fi

file=$1
SEED=$2

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "Error: File '$file' not found!"
  exit 1
fi

# Find all occurrences of "(_BitInt(any_number))" with their line and column numbers
candidates=$(grep -noE "\(_BitInt\([0-9]+\)\)" "$file" | awk -F: '{print $1 ":" $2}')

# Check if any candidates exist
if [ -n "$candidates" ]; then
  # Randomly pick one occurrence
  random_candidate=$(echo "$candidates" | awk -v seed="(($SEED))" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
  line_number=$(echo "$random_candidate" | cut -d: -f1)
  col_number=$(echo "$random_candidate" | cut -d: -f2)

  # Use sed to remove the selected pattern
  sed -i -E "${line_number}s/\(_BitInt\([0-9]+\)\)//" "$file"

  echo "Removed pattern at line $line_number, column $col_number in file: $file"
fi

# Find all occurrences of '_BitInt(X)' where X is any number and get line and column numbers
matches=$(grep -noE '_BitInt\([0-9]+\)' "$file" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Check if matches are found
if [ -n"$matches" ]; then
  # Extract line and column from the random match
  line=$(echo "$matches" | cut -d: -f1)
  content=$(echo "$matches" | cut -d: -f2-)

  # Extract the current size (X) from '_BitInt(X)'
  current_size=$(echo "$content" | grep -oE '[0-9]+')

  # Calculate the new size
  new_size=$((current_size - 1))

  # Update the file with the incremented size
  sed -i -E "${line}s/_BitInt\(${current_size}\)/_BitInt(${new_size})/" "$file"

  echo "Updated '_BitInt(${current_size})' to '_BitInt(${new_size})' at line $line."
fi
