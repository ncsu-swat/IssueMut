#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

longVars=$(grep -oE "long\s+[a-zA-Z_][a-zA-Z0-9_]*\s*;" "$file" | \
sed -E 's/long\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*;/\1'/)

if [ -z "$longVars" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match1=$(echo "$longVars" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
longVar=$(echo "$random_match1" | cut -d: -f1)

sed -i -E "/long\s+$longVar\s*;/d" "$file"

funcNames=$(grep -oE "void\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(.*\)" "$file" | \
sed -E 's/void\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\(.*\)/\1'/)

if [ -z "$funcNames" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match2=$(echo "$funcNames" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
funcName=$(echo "$random_match2" | cut -d: -f1)

sed -i -E "s/([^a-zA-Z0-9_])${longVar}([^a-zA-Z0-9_])/\1(__INTPTR_TYPE__\)${funcName}\2/g" "$file"