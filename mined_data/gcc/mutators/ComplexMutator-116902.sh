#!/bin/bash

# Ensure a file is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Define sed expressions
sed_expr1='for\s*\((.*)\s*=\s*(.*);(.*);(.*)\+\+\s*\)/for (\1;\4;\4++)'
sed_expr2='for\s*\((.*);(.*)<(.*);(.*)\)/for (\1;\2< 17;\4)'
sed_expr3='for\s*\((.*)\s*=\s*(.*);(.*);(.*)\+\+\)/for (\1;\3;\4 += ~0)'

# Temporary files to hold candidates
temp_candidates1=$(mktemp)
temp_candidates2=$(mktemp)
temp_candidates3=$(mktemp)

# Collect candidate lines for each expression
grep -nE 'for\s*\(.*=.*;.*;.*\+\+.*\)' "$file" > "$temp_candidates1" # Expression 1 and 3 overlap
grep -nE 'for\s*\(.*;.*<.*;.*\)' "$file" > "$temp_candidates2"
grep -nE 'for\s*\(.*=.*;.*;.*\+\+.*\)' "$file" > "$temp_candidates3" # Overlap with 1

# Function to randomly apply a sed expression to a candidate
apply_random_sed() {
    local candidates_file="$1"
    local sed_expr="$2"
    local file="$3"
    
    # Get the number of candidates
    num_candidates=$(wc -l < "$candidates_file")
    if [ "$num_candidates" -eq 0 ]; then
        return 0  # No candidates found, skip
    fi

    # Select a random candidate
    random_line=$("$candidates_file" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
    line_number=$(echo "$random_line" | cut -d: -f1)
    
    # Apply the sed expression to the selected line
    sed -i -E "${line_number}s/$sed_expr/" "$file"
}

# Randomly apply each expression
apply_random_sed "$temp_candidates1" "$sed_expr1" "$file"
apply_random_sed "$temp_candidates2" "$sed_expr2" "$file"
apply_random_sed "$temp_candidates3" "$sed_expr3" "$file"

# Cleanup temporary files
rm "$temp_candidates1" "$temp_candidates2" "$temp_candidates3"

echo "Random transformations applied to file: $file"