#!/bin/bash

# If the number of arguments is not equal to 2 then exit and print error message
if [ $# -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
fi

file="$1"
# Correct sed command to remove extern "C"
sed -i -E 's/extern[[:space:]]*"C"[[:space:]]*//g' "$file"