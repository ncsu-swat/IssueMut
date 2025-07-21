#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find a random attribute, add environment = pixel
first=$(grep -noE '__attribute__\(\(availability\([^)]*\)\)\)' "$file" | grep -v 'environment')
if [ -z "$first" ]; then
    echo "No matching patterns found."
    exit 0
fi
first_random=$(echo "$first" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
first_line=$(echo "$first_random" | cut -d: -f1)

sed -i -E "${first_line} s/(__attribute__\(\(availability\([^)]*)\)\)\)/\1, environment = pixel\)\)\)/" "$file"

# Find a random attribute, add environment = compute
second=$(grep -noE '__attribute__\(\(availability\([^)]*\)\)\)' "$file" | grep -v 'environment')
if [ -z "$second" ]; then
    echo "No matching patterns found."
    exit 0
fi
second_random=$(echo "$second" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
second_line=$(echo "$second_random" | cut -d: -f1)

sed -i -E "${second_line} s/(__attribute__\(\(availability\([^)]*)\)\)\)/\1, environment = compute\)\)\)/" "$file"

# Find a random attribute, add environment = mesh
third=$(grep -noE '__attribute__\(\(availability\([^)]*\)\)\)' "$file" | grep -v 'environment')
if [ -z "$third" ]; then
    echo "No matching patterns found."
    exit 0
fi
third_random=$(echo "$third" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
third_line=$(echo "$third_random" | cut -d: -f1)

sed -i -E "${third_line} s/(__attribute__\(\(availability\([^)]*)\)\)\)/\1, environment = mesh\)\)\)/" "$file"

# Find a random attribute, add environment = amplification
fourth=$(grep -noE '__attribute__\(\(availability\([^)]*\)\)\)' "$file" | grep -v 'environment')
if [ -z "$fourth" ]; then
    echo "No matching patterns found."
    exit 0
fi
fourth_random=$(echo "$fourth" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
fourth_line=$(echo "$fourth_random" | cut -d: -f1)

sed -i -E "${fourth_line} s/(__attribute__\(\(availability\([^)]*)\)\)\)/\1, environment = amplification\)\)\)/" "$file"