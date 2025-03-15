#!/bin/bash

# Check for correct number of arguments
if [ $# -ne 3 ]; then
  echo "Usage: $0 <file> <pattern> <replacement>"
  exit 1
fi

FILE="$1"
PATTERN="$2"
REPLACEMENT="$3"

# Check if the file exists
if [ ! -f "$FILE" ]; then
  echo "Error: File '$FILE' not found."
  exit 1
fi

# Find all matching lines containing the pattern using grep (no -P option)
matches=$(grep -n "$PATTERN" "$FILE" | shuf -n 1)

if [ -z "$matches" ]; then
  echo "No matches found for the pattern '$PATTERN'."
  exit 1
fi

# Extract the line number from the match
line_number=$(echo "$matches" | cut -d: -f1)

# Use sed to replace the first occurrence on the randomly selected line
# Obs. the extra argument "" is necessary only in MacOS. It is unnecessary (and not used) on Linux
sed -i "" "${line_number}s/$PATTERN/$REPLACEMENT/" "$FILE"

echo "Replaced a random occurrence of '$PATTERN' in line $line_number with '$REPLACEMENT'."