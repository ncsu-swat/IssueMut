#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

# Remove a value from constexpr variable initializer
sed -i -E 's/constexpr (.*) = \{([^}]*), ([^,]*)\};/constexpr \1 = {\2};/' "$file"
