#!/bin/bash

# Check if a file argument is provided
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

input_file="$1"
SEED=$2

# Validate if the input file exists
if [ ! -f "$input_file" ]; then
  echo "Error: File '$input_file' not found."
  exit 1
fi

# Find all matching locations and extract variable names and loop limits
matches=$(awk '
/.*\+=\s*\*.*;/{ 
  var_line = NR
  sub(/;$/, "", $3)
  sub(/\*/, "", $3)
  var_name = $3
  getline
  if ($0 ~ var_name "\\+\\+;") {
    print var_line "," NR
  }
}' "$input_file")

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Convert matches to an array and randomly pick one
random_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Extract details from the selected match
start_line=$(echo "$random_match" | cut -d',' -f1)
end_line=$(echo "$random_match" | cut -d',' -f2)

# Apply the transformation
sed -i -E "${start_line}s/(.*)\+=\s*(.*);/\1 += \2\+\+;/" "$input_file"
sed -i -E "${end_line}d" "$input_file"

echo "Transformation applied at lines $start_line to $end_line."