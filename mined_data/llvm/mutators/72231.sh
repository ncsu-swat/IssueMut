#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[[:space:]]*#pragma[[:space:]]+omp[[:space:]]+parallel/ {
    :find_brace
    n
    # If another omp pragma or a scope-closing brace is found before the
    # opening brace of the parallel region, it implies a single-statement
    # parallel region or some other construct. Stop processing this region.
    /^[[:space:]]*#pragma[[:space:]]+omp/ b
    /^[[:space:]]*\}/ b

    /\{/ {
        :find_barrier
        n
        # If the closing brace of the parallel region is found, stop.
        /^[[:space:]]*\}/ b
        # Skip empty lines or comments.
        /^[[:space:]]*($|\/\/|\/\*)/ b find_barrier
        # If the first non-empty, non-comment line is a barrier, delete it.
        /^[[:space:]]*#pragma[[:space:]]+omp[[:space:]]+barrier/d
        # Whether a barrier was deleted or not, we are done with this region
        # as we only care about the very first barrier.
        b
    }
    # Continue searching for the opening brace on the next line.
    b find_brace
}
' "$file"