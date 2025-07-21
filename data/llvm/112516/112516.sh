#!/bin/bash

# Usage: ./replace_constexpr.sh file.c seed

if [ $# -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

file="$1"
SEED=$2

# Find constexpr variable declarations
constexprs=$(grep -nE "constexpr\s+[a-zA-Z_]\w*\s+[a-zA-Z_]\w*\s*=\s*[0-9]+" "$file" | \
  sed -E "s/^([0-9]+):.*constexpr\s+[a-zA-Z_]\w*\s+([a-zA-Z_]\w*)\s*=\s*([0-9]+);.*/\1:\2:\3/")

if [ -z "$constexprs" ]; then
  echo "No constexpr found."
  exit 1
fi

# Find struct pointer declarations
struct_ptrs=$(grep -nE "struct\s+[a-zA-Z_]\w*\s*\*\s*[a-zA-Z_]\w*" "$file" | \
  sed -E "s/^([0-9]+):.*struct\s+([a-zA-Z_]\w*)\s*\*\s*([a-zA-Z_]\w*).*/\1:\2:\3/")

if [ -z "$struct_ptrs" ]; then
  echo "No struct pointer found."
  exit 1
fi

# Randomly select entries
constexpr_entry=$(echo "$constexprs" | awk -v seed="$SEED" 'BEGIN{srand(seed)} {if (rand() <= 1/NR) sel=$0} END{print sel}')
struct_entry=$(echo "$struct_ptrs" | awk -v seed="$SEED+1" 'BEGIN{srand(seed)} {if (rand() <= 1/NR) sel=$0} END{print sel}')

# Extract info
constexpr_line=$(echo "$constexpr_entry" | cut -d: -f1)
constexpr_var=$(echo "$constexpr_entry" | cut -d: -f2)
struct_type=$(echo "$struct_entry" | cut -d: -f2)
struct_var=$(echo "$struct_entry" | cut -d: -f3)

# Extract field from struct definition
struct_body=$(awk "/struct\s+${struct_type}\s*{/,/};/" "$file")

field=$(echo "$struct_body" | grep -E "[a-zA-Z_]\w*\s+[a-zA-Z_]\w*;" | \
  sed -E "s/.*\s+([a-zA-Z_]\w*)\s*;.*/\1/" | awk -v seed="$SEED" 'BEGIN{srand(seed)} {if (rand() <= 1/NR) f=$1} END{print f}')

if [ -z "$field" ]; then
  echo "No field found in struct $struct_type."
  exit 1
fi

# Replace the constexpr initializer with struct pointer field
sed -i "${constexpr_line}s/\(constexpr\s\+[a-zA-Z_]\w*\s\+${constexpr_var}\s*=\s*\)[0-9]\+/\1${struct_var}->${field}/" "$file"
