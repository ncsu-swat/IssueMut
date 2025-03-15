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

# Temporary file to store modified content
TEMP_FILE=$(mktemp)

echo "Processing file: $FILE"
echo "Writing modified content to temporary file: $TEMP_FILE"

# Read the file line by line
while IFS= read -r line || [ -n "$line" ]; do
    echo "Reading line: $line"  # Debugging output

    # Write the original line to the temp file
    echo "$line" >> "$TEMP_FILE"

    # Check if the line contains an extern function declaration
    if echo "$line" | grep -Eq '\s*extern\s*.*\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\(.*\)\s*;'; then
        echo "Matched extern declaration: $line"  # Debugging output
        # Replace extern with static
        new_line="${line/extern/static}"
        echo "Adding static version: $new_line"  # Debugging output
        echo "$new_line" >> "$TEMP_FILE"
    fi

    # Check if the line contains a static function declaration
    if echo "$line" | grep -Eq '\s*static\s*.*\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\(.*\)\s*;'; then
        echo "Matched static declaration: $line"  # Debugging output
        # Replace static with extern
        new_line="${line/static/extern}"
        echo "Adding extern version: $new_line"  # Debugging output
        echo "$new_line" >> "$TEMP_FILE"
    fi
done < "$FILE"

# Replace the original file with the modified content
mv "$TEMP_FILE" "$FILE"

echo "Duplicated function declarations with opposite linkage in $FILE."