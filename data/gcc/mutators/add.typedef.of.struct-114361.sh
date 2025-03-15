#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

matches=$(awk '
/struct[ \t]+[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\{/ {name=$2} name && $0 ~ "struct[ \t]+" name ".*[a-zA-Z_]" {print name}
' "$file")


if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 1
fi

# Randomly pick one
type=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

struct_def=$(sed -n "/struct $type {/,/};/p" "$file" | sed ':a;N;$!ba;s/\n/\\n/g')

sed -i -E "s/([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(.*\) \{)/\1${struct_def}/" "$file"

sed -i -E "s/struct $type( .*;)/struct b\1/" "$file"

sed -i "1i typedef struct $type b;" "$file"
sed -i "1i struct $type;" "$file"
