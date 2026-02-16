#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Look for __attribute__ where the target version is default
default=$(grep -noE "__attribute__\(\(target_version\(\"default\"\)\)\) [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(\) \{ return .*; \}" "$file")
if [ -z "$default" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match1=$(echo "$default" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
defaultLine=$(echo "$random_match1" | cut -d: -f1)
defaultMethod=$(echo "$random_match1" | cut -d: -f2)

# Look for other __attribute__ method
other=$(grep -noE "__attribute__\(\(target_version\(\".*\"\)\)\) [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(\) \{ return .*; \}" "$file")
if [ -z "$other" ]; then
  echo "No matching patterns found."
  exit 0
fi

random_match2=$(echo "$other" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
otherLine=$(echo "$random_match2" | cut -d: -f1)

# Place the default method in front of the other method if the default method is placed after the other method
if [ "$defaultLine" -gt "$otherLine" ]; then
    sed -i -E "${defaultLine} s/__attribute__\(\(target_version\(\"default\"\)\)\) [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]*\(\) \{ return .*; \}//" "$file"
    sed -i -E "${otherLine} i${defaultMethod}" "$file"
fi
