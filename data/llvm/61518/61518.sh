#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED="$2"

double_matches=$(grep -n -E "^(_Complex double)" "$file")

float_matches=$(grep -n -E "^(_Complex float)" "$file")

random_double=$(echo "$double_matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() < 1/NR) line=$0} END {print line}')

random_float=$(echo "$float_matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() < 1/NR) line=$0} END {print line}')

line_number_double=$(echo "$random_double" | awk -F ":" '{print $1}')

line_number_float=$(echo "$random_float" | awk -F ":" '{print $1}')

sed -i -E "${line_number_double}s/}/, 3.0}/" "$file"

sed -i -E "${line_number_float}s/}/, 3.3f, 4.4f}/" "$file"
