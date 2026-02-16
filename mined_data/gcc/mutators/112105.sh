#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Save the name of the last variable used inside of a vmul_n_f32
matches=$(grep -oE 'vmul_n_f32\(.*, [a-zA-Z_][a-zA-Z0-9_]*\)' "$file" | \
sed -E "s/vmul_n_f32\(.*, ([a-zA-Z_][a-zA-Z0-9_]*)\)/\1/")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

scalar=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')


# Find the declaration for that variable, save the content
declarations=$(grep -noE "$scalar = vget_lane_f32\(.*\);" "$file" | \
sed -E "s/$scalar = vget_lane_f32\((.*)\);/\1/")

if [ -z "$declarations" ]; then
  echo "No matching patterns found."
  exit 0
fi

declaration=$(echo "$declarations" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$declaration" | cut -d: -f1)
value=$(echo "$declaration" | cut -d: -f2)

# Delete the declaration and replace the variable name with the content
sed -i -E "$line d" "$file"
sed -i -E "s/vmul_n_f32\((.*,) $scalar\)/vmul_lane_f32\(\1 $value\)/" "$file"