#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename> <seed>"
    exit 1
fi

TEMP_FILE=$(mktemp)

# Use awk to perform the flexible transformation
awk '{
    while (match($0, /-([0-9]+)L - 1/)) {
        num = substr($0, RSTART + 1, RLENGTH - 6)  # Extract the number dynamically
        replacement = (num + 1) "UL"               # Compute the replacement value
        $0 = substr($0, 1, RSTART - 1) replacement substr($0, RSTART + RLENGTH)  # Replace
    }
    print
}' "$1" > "$TEMP_FILE" && mv "$TEMP_FILE" "$1"

echo "Replacement complete in file: $1"