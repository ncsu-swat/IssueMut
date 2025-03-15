#!/usr/bin/env bash
# Usage: ./convert_do_while_to_for.sh <file>
#
# 1) Looks for "do {" and changes it to "for (; i >= 0; i--) {"
# 2) Looks for "} while (1);" and changes it to "}"

if [ $# -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

file="$1"
if [ ! -f "$file" ]; then
  echo "Error: '$file' not found!"
  exit 1
fi

# Use sed to do two substitutions in-place (-i):
#   a) Replace lines containing "do {" with "for (; i >= 0; i--) {"
#   b) Replace lines containing "} while (1);" with "}"
sed -i -E '
  s/^[[:space:]]*do[[:space:]]*\{/for (; i >= 0; i--) {/;
  s/^[[:space:]]*\}[[:space:]]*while[[:space:]]*\(\s*1\s*\)[[:space:]]*;[[:space:]]*$/}/;
' "$file"

echo "Converted do-while(1) to for(; i >= 0; i--) in '$file'."