#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# A method to add gnu
methods1=$(grep -noE "__attribute__\(\(no_stack_protector\)\)" "$file")

if [ -z "$methods1" ]; then
  echo "No matching patterns found."
  exit 0
fi

method1=$(echo "$methods1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line1=$(echo "$method1" | cut -d: -f1)

sed -i -E "$line1 s/(.*) __attribute__\(\(no_stack_protector\)\) (.*)/\[\[gnu::no_stack_protector\]\] \1 \2/" "$file"


# A method to add clang
methods2=$(grep -noE "__attribute__\(\(no_stack_protector\)\)" "$file")

if [ -z "$methods2" ]; then
  echo "No matching patterns found."
  exit 0
fi

method2=$(echo "$methods2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

line2=$(echo "$method2" | cut -d: -f1)

sed -i -E "$line2 s/(.*) __attribute__\(\(no_stack_protector\)\) (.*)/\[\[clang::no_stack_protector\]\] \1 \2/" "$file"
