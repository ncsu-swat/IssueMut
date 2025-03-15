#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename.c> <seed>"
    exit 1
fi

# Input file
FILE="$1"

# Check if the file exists
if [ ! -f "$FILE" ]; then
    echo "File not found!"
    exit 1
fi

# Create a temporary file to store removed lines
REMOVED_LINES=$(mktemp)

# Extract and remove 'register' variable declarations, saving removed lines
sed -n '/\bregister\b[^;]*;/p' "$FILE" > "$REMOVED_LINES"
sed -i '/\bregister\b[^;]*;/d' "$FILE"

# Extract variable names from removed lines
declare -A VARIABLES
while IFS= read -r line; do
    # Use grep and sed to extract the variable name
    var_name=$(echo "$line" | grep -oE '\bregister\b[^;]* ([a-zA-Z_][a-zA-Z0-9_]*) *;' | sed -E 's/.* ([a-zA-Z_][a-zA-Z0-9_]*) *;/\1/')
    if [ -n "$var_name" ]; then
        VARIABLES["$var_name"]="$line"
    fi
done < "$REMOVED_LINES"

# Replace references with the assigned variable
for var in "${!VARIABLES[@]}"; do
    # Find the first assignment for the variable
    ASSIGNED_VAR=$(grep -E "\b${var}\b\s*=" "$FILE" | sed -E "s/.*\b${var}\b\s*=\s*([^;]*);.*/\1/" | head -n 1)

    if [ -n "$ASSIGNED_VAR" ]; then
        # Replace all references to the variable with the assigned variable
        sed -i -E "s/.*\b${var}\b\s*=\s*([^;]*);.*//" "$FILE"
        sed -i "s/\b${var}\b/${ASSIGNED_VAR}/g" "$FILE"
    else
        echo "No assignment found for $var; skipping replacement."
    fi
done

# Clean up temporary file
rm "$REMOVED_LINES"

echo "All references to removed variables have been replaced with assigned variables."