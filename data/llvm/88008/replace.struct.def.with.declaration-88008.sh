#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

structs=$(grep -oE "struct [a-zA-Z_][a-zA-Z0-9_]* \{" "$file" | \
sed -E "s/struct ([a-zA-Z_][a-zA-Z0-9_]*) \{/\1/")
if [ -z "$structs" ]; then
  echo "No matching patterns found.."
  exit 0
fi
struct_name=$(echo "$structs" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# Find struct type declaration, delete the entire struct except struct struct_name;
awk -v target="$struct_name" '
BEGIN { RS=""; FS="\n" }
{
    if ($0 ~ "^struct " target " \\{[^}]*\\};") {
        print "struct " target ";"
        next
    }
    print
}' "$file" > "${file}.tmp" && mv "${file}.tmp" "$file"

# Handle multi-line definitions of the target struct
sed -i -E "/struct $struct_name \{/,/\};/ {
    /struct $struct_name \{/ {
        s/struct $struct_name \{.*/struct $struct_name;/;t
        b
    }
    d
}" "$file"