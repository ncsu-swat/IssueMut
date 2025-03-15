#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename> <seed>"
    exit 1
fi

TEMP_FILE=$(mktemp)

# Perform the transformation using sed
sed -E '
    # Replace 0xFFU with (__mmask8) -1
    s/\b0xFFU\b/\(__mmask8\) -1/g

    # Replace 0xFFFFU with (__mmask16) -1
    s/\b0xFFFFU\b/\(__mmask16\) -1/g

    # Replace 0xFFFFFFFFU with (__mmask32) -1
    s/\b0xFFFFFFFFU\b/\(__mmask32\) -1/g

    # Replace 0xFFFFFFFFFFFFFFFFULL with (__mmask64) -1
    s/\b0xFFFFFFFFFFFFFFFFULL\b/\(__mmask64\) -1/g
' "$1" > "$TEMP_FILE" && mv "$TEMP_FILE" "$1"

echo "Transformation complete in file: $1"