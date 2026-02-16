#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

matches=$(grep -noE 'int [a-zA-Z_][a-zA-Z0-9_]* = [a-zA-Z_][a-zA-Z0-9_]* \& .*;' "$file" | \
sed -E "s/int ([a-zA-Z_][a-zA-Z0-9_]*) = ([a-zA-Z_][a-zA-Z0-9_]*) \& .*;/\1:\2/")

if [ -z "$matches" ]; then
  echo "No matching patterns found."
  exit 0
fi

rand_match=$(echo "$matches" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line=$(echo "$rand_match" | cut -d: -f1)
tmp=$(echo "$rand_match" | cut -d: -f2)
a=$(echo "$rand_match" | cut -d: -f3)

sed -i -E "$line s/int [a-zA-Z_][a-zA-Z0-9_]* = ([a-zA-Z_][a-zA-Z0-9_]*) \& (.*);/\1 \&= \2;/" "$file"

sed -i -E "s/$tmp/$a/g" "$file"

sed -i -E "s/return \((.*)\);/return \1;/" "$file"