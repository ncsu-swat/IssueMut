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
/int\s+[a-zA-Z_][a-zA-Z0-9_]*\s*;/{ 
  var_line = NR
  sub(/;$/, "", $2)
  var_name = $2
  getline
  if ($0 ~ "for\\s*\\(\\s*" var_name "\\s*=\\s*0\\s*;\\s*" var_name "\\s*<.*[0-9]+\\s*;\\s*" var_name "\\+\\+\\s*\\)") {
    match($0, /<.*([0-9]+);/, limit)
    print var_line "," NR "," var_name "," limit[1]
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
variable_name=$(echo "$random_match" | cut -d',' -f3)
loop_limit=$(echo "$random_match" | cut -d',' -f4)

# Apply the transformation
sed -i -E "${start_line}s/(int\s+${variable_name})\s*;/\1 = ${loop_limit};/" "$input_file"
sed -i -E "${end_line}s/for\s*\(\s*${variable_name}\s*=\s*0\s*;\s*${variable_name}\s*<.*[0-9]+\s*;\s*${variable_name}\+\+\s*\)/for (; ${variable_name} >= 0; --${variable_name})/" "$input_file"

echo "Transformation applied at lines $start_line to $end_line, variable: $variable_name, limit: $loop_limit."