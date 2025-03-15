#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename> <seed>"
    exit 1
fi

TEMP_FILE=$(mktemp)

# Use awk to process the file and reduce the vector size
awk '{
    if (match($0, /__vector_size__\s*\(([0-9]+)\)/, arr)) {
        original = arr[1]
        new_size = int(original / 2)  # Ensure integer division
        gsub(/__vector_size__\s*\([0-9]+\)/, "__vector_size__ (" new_size ")", $0)
    }
    print
}' "$1" > "$TEMP_FILE" && mv "$TEMP_FILE" "$1"

echo "Vector size reduced by half in file: $1"