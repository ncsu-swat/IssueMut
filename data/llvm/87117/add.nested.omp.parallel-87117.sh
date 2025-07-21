#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Change 1 to 2 in omp_set_max_active levels
# and add omp parallel num_threads(2) and a { in next lines
sed -i -E "s/omp_set_max_active_levels\(1\);/omp_set_max_active_levels\(2\);/" "$file"

# Get a random parallel num_threads line
num_threads=$(grep -noE "#pragma omp parallel num_threads\([0-9]+\)" "$file" | \
sed -E "s/#pragma omp parallel num_threads\(([0-9]+)\)/\1/")
if [ -z "$num_threads" ]; then
  echo "No matching patterns found."
  exit 0
fi
rand_match=$(echo "$num_threads" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

threads_line=$(echo "$rand_match" | cut -d: -f1)
threads_num=$(echo "$rand_match" | cut -d: -f2)

# Add another statement and a opening curly brace above
sed -i -E "${threads_line}i\
\{" "$file"

sed -i -E "${threads_line}i\
#pragma omp parallel num_threads\($threads_num\)" "$file"

start_line=$((threads_line + 2))

# Loop to find the find first opening curly brace and its matching closing curly brace
# Add an extra closing curly brace 
if [ -n "$start_line" ]; then
    # Find first opening brace after modification
    opening_brace_line=$(awk -v start="$start_line" '
        NR >= start && /{/ {print NR; exit}
    ' "$file")

    if [ -n "$opening_brace_line" ]; then
        # Find matching closing brace
        brace_count=1
        closing_brace_line=$opening_brace_line
        
        awk -v start="$opening_brace_line" '
        NR >= start {
            if (/{/) brace_count++
            if (/}/) brace_count--
            if (brace_count == 0) {
                print NR
                exit
            }
        }
        ' "$file" | while read -r match_line; do
            # Insert closing brace after the match
            sed -i "${match_line}a}" "$file"
        done
    fi
fi