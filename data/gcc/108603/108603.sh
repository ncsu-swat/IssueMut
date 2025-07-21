#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script finds the first line that looks like a global array declaration of type 'long long'
# and changes its type to 'int'. It then stops trying to make changes and just prints the rest of the file.
#
# Breaking down the sed command:
# /<pattern>/ { ... }
#   - This finds a line matching <pattern> and executes the commands in {}.
# <pattern>: ^[[:space:]]*((static|extern)[[:space:]]+)?long long[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\[
#   - ^[[:space:]]*                  - Optional whitespace at the start of the line.
#   - ((static|extern)[[:space:]]+)? - Optional 'static' or 'extern' keyword.
#   - long long[[:space:]]+          - The type 'long long'.
#   - [a-zA-Z_][a-zA-Z0-9_]*         - A C identifier for the array name.
#   - [[:space:]]*\[                 - Optional whitespace and an opening bracket, indicating an array.
#
# Commands in {}:
# s/long long/int/
#   - Substitutes the first occurrence of 'long long' with 'int' on the matched line.
# :a; n; ba
#   - This is a sed idiom to print the rest of the file without further processing.
#   - :a    - Defines a label 'a'.
#   - n     - Prints the current pattern space, then reads the next line of input.
#   - ba    - Branches (jumps) to label 'a'.
#   - This effectively creates a loop that reads and prints each remaining line until the end of the file.
#
# This ensures that only the *first* matching global array is modified, which fixes the issue from the original script.

sed -i -E '/^[[:space:]]*((static|extern)[[:space:]]+)?long long[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\[/ { s/long long/int/; :a; n; ba; }' "$file"