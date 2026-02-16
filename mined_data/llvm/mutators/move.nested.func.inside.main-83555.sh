#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find nested function
matches=$(grep -noE '[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*\) \{.*\};' "$file")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

nestedLine=$(echo "$rand_match" | cut -d: -f1)
nestedFunc=$(echo "$rand_match" | cut -d: -f2)

# Delete the nested function
sed -i -E "${nestedLine} s/[a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*\) \{.*\};//" "$file"


# Find main function
main=$(grep -noE 'int main\(.*\) \{' "$file")
mainLine=$(echo "$main" | cut -d: -f1)

# Place nested function inside main
sed -i -E "${mainLine} a\\
$nestedFunc" "$file"


# Find a #include statement
include=$(grep -noE '#include .*' "$file" | tail -n 1)
if [ -z "$include" ]; then
  echo "No matching patterns found."
  exit 0
fi
includeLine=$(echo "$include" | cut -d: -f1)

# Add #if after the selected line
sed -i -E "${includeLine} a\\
#if \!defined\(__clang__\)" "$file"


# Add the following lines at the end of the file
sed -i -E '$a\
#else\
\
int main\(\) \{\
  printf\(\"skipped\\n\");\
  return 0;\
\}\
\
#endif' "$file"
