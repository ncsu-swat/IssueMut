#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E "s/unsigned\s+long/__SIZE_TYPE__/g" "$file"

sed -i -E "s/long\s+long/__INT64_TYPE__/g" "$file"

matches=$(grep -oE 'volatile\s+[a-zA-Z_][a-zA-Z0-9_]*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;' "$file" | \
sed -E 's/volatile\s+[a-zA-Z_][a-zA-Z0-9_]*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;/\1,\2/')

# If no matches are found, exit
if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

for match in $matches; do
  volatile_variable=$(echo "$match" | cut -d',' -f1)
  variable=$(echo "$match" | cut -d',' -f2)

  sed -i -E 's/volatile\s+[a-zA-Z_][a-zA-Z0-9_]*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*;//' "$file"

  sed -i -E "s/([^a-zA-Z0-9_])$volatile_variable([^a-zA-Z0-9_])/\1$variable\2/g" "$file"
done
