#!/bin/bash

# Check for correct number of arguments
if [ $# -ne 4 ]; then
  echo "Usage: $0 <file> <pattern> <replacement> <seed>"
  exit 1
fi

FILE=$1
PATTERN=$2
REPLACEMENT=$3
SEED=$4

# Check if the file exists
if [ ! -f "$FILE" ]; then
  echo "Error: File '$FILE' not found."
  exit 1
fi

# Find all matching lines containing the pattern using grep (no -P option)
matches=$(grep -nE "$PATTERN" "$FILE" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# echo $matches

if [ -z "$matches" ]; then
  echo "No matches found for the pattern '$PATTERN'."
  exit 1
fi

# Extract the line number from the match
line_number=$(echo "$matches" | cut -d: -f1)

# Use sed to replace the first occurrence on the randomly selected line
# Obs. the extra argument "" is necessary only in MacOS. It is unnecessary (and not used) on Linux
sed -Ei "${line_number}s/$PATTERN/$REPLACEMENT/" $FILE

# echo "Replaced a random occurrence of '$PATTERN' in line $line_number with '$REPLACEMENT'."

# cat $FILE