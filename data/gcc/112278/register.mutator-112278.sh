#!/usr/bin/env bash
#
# Usage: ./rename_registers_to_v0.sh <file>
#  - Finds lines matching:   register <type> <var_name> asm ("..."); 
#  - Extracts <var_name>, then replaces ALL occurrences of <var_name> with "v0".
#  - In-place modification of <file>.

if [ $# -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

input_file="$1"

if [ ! -f "$input_file" ]; then
  echo "Error: '$input_file' not found."
  exit 1
fi

# 1) Extract all variable names declared as register variables with asm("...")
#    For example: "register svint8_t sve_v0 asm ("z0");"
#    We'll capture the <var_name> part. 
vars=$(grep -E 'register\s+[a-zA-Z0-9_]+\s+[a-zA-Z0-9_]+\s+asm' "$input_file" \
  | sed -E 's/.*register\s+[a-zA-Z0-9_]+\s+([a-zA-Z0-9_]+)\s+asm.*/\1/g')

# 2) For each extracted variable name, replace it with "v0" throughout the file.
for var in $vars; do
  sed -i "s/\b${var}\b/v0/g" "$input_file"
done

echo "All register variables renamed to 'v0'."


sed -i -E 's/\"=z\"/\"=w\"/' "$input_file"
sed -i -E 's/asm\s*\(\s*\"v1\"\s*\)/asm (\"v0\")/' "$input_file"