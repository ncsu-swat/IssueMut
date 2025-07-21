#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# Pre-process to handle main() signature split across lines
sed -i -E ':a;N;$!ba;s/int\s*\n\s*main/int main/g' "$file"

# Remove test-related includes and the main function itself.
# The key fix is to find the line where main() starts and delete from
# there to the end of the file ($). This is a robust heuristic for
# self-contained test programs, avoiding the fragile brace-counting
# problem which caused the original script to fail.
sed -i -E \
    -e '/^#include <(stdio|stdlib|limits)\.h>/d' \
    -e '/^\s*int\s+main\s*\(.*/,$d' \
    "$file"

# Clean up excessive newlines and trailing whitespace from the result.
# This is done as a final pass to ensure consistent formatting.
sed -i -E '
    :a;
    N;
    $!ba;
    s/\n\n+/\n\n/g;
    s/^\n+//;
    s/\n\s*$/\n/;
' "$file"