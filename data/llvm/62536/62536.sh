#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all headers that contain tye type uint32_t as parameter
headers=$(grep -noE 'int [a-zA-Z_][a-zA-Z0-9_]*\(uint32_t [a-zA-Z_][a-zA-Z0-9_]*\)' "$file" | \
sed -E "s/int [a-zA-Z_][a-zA-Z0-9_]*\(uint32_t ([a-zA-Z_][a-zA-Z0-9_]*)\)/\1/")

if [ -z "$headers" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Pick a random header and change uint32_t to *__ptr32 __uptr
header=$(echo "$headers" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
headerLine=$(echo "$header" | cut -d: -f1)
param=$(echo "$header" | cut -d: -f2)

sed -i -E "${headerLine} s/int ([a-zA-Z_][a-zA-Z0-9_]*)\(uint32_t ([a-zA-Z_][a-zA-Z0-9_]*)\)/int \1\(int \*__ptr32 __uptr \2\)/" "$file"

# Find where the variable is declared
variables1=$(grep -noE "uint64_t [a-zA-Z_][a-zA-Z0-9_]* = ${param};" "$file" | \
sed -E "s/uint64_t ([a-zA-Z_][a-zA-Z0-9_]*) = ${param};/\1/")

if [ -z "$variables1" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Pick a random line and save its line number and the variable it is equal to 
varaible1=$(echo "$variables1" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
variableLine1=$(echo "$varaible1" | cut -d: -f1)
variableName1=$(echo "$varaible1" | cut -d: -f2)

# Delete the line
sed -i -E "${variableLine} s/uint64_t [a-zA-Z_][a-zA-Z0-9_]* = ${param};//" "$file"


# Find where the pointer is declared
variables2=$(grep -noE "int \*[a-zA-Z_][a-zA-Z0-9_]* = \(int \*\)${variableName1};" "$file" | \
sed -E "s/int \*([a-zA-Z_][a-zA-Z0-9_]*) = \(int \*\)${variableName1};/\1/")

if [ -z "$variables2" ]; then
  echo "No matching patterns found."
  exit 0
fi

# Pick a random declaration and save its line number and the variable it is equal to
varaible2=$(echo "$variables2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
variableLine2=$(echo "$varaible2" | cut -d: -f1)
variableName2=$(echo "$varaible2" | cut -d: -f2)

# Delete the line
sed -i -E "${variableLine2} s/int \*[a-zA-Z_][a-zA-Z0-9_]* = \(int \*\)${variableName1};//" "$file"

# Whenever the pointer name is called, replace it with the variable it is equal to
sed -i -E "s/${variableName2}/${param}/g" "$file"






# # Pick a random declaration and save its line number and the pointer name
# pointer=$(echo "$pointers" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
# pointerLine=$(echo "$pointer" | cut -d: -f1)
# pointerName=$(echo "$pointer" | cut -d: -f2)

# # Find all variable declarations where it is set to a pointer
# pointers=$(grep -noE "int [a-zA-Z_][a-zA-Z0-9_]* = \*[a-zA-Z_][a-zA-Z0-9_]*;" "$file" | \
# sed -E 's/int [a-zA-Z_][a-zA-Z0-9_]* = \*([a-zA-Z_][a-zA-Z0-9_]*);/\1/')

# if [ -z "$pointers" ]; then
#   echo "No matching patterns found."
#   exit 0
# fi
# echo "$pointers"

# # Pick a random declaration and save its line number and the pointer name
# pointer=$(echo "$pointers" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
# pointerLine=$(echo "$pointer" | cut -d: -f1)
# pointerName=$(echo "$pointer" | cut -d: -f2)


# # Find where the pointer is declared
# variables=$(grep -noE "int \*${pointerName} = \(int \*\)[a-zA-Z_][a-zA-Z0-9_]*;" "$file" | \
# sed -E "s/int \*${pointerName} = \(int \*\)([a-zA-Z_][a-zA-Z0-9_]*);/\1/")

# if [ -z "$variables" ]; then
#   echo "No matching patterns found."
#   exit 0
# fi
# echo "$variables"

# # Pick a random declaration and save its line number and the variable it is equal to
# varaible=$(echo "$variables" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
# variableLine=$(echo "$varaible" | cut -d: -f1)
# variableName=$(echo "$varaible" | cut -d: -f2)

# # Delete the line
# sed -i -E "${variableLine} s/int \*${pointerName} = \(int \*\)[a-zA-Z_][a-zA-Z0-9_]*;//" "$file"


# # Find where the variable is declared
# variables2=$(grep -noE "uint64_t ${variableName} = [a-zA-Z_][a-zA-Z0-9_]*;" "$file" | \
# sed -E "s/uint64_t ${variableName} = ([a-zA-Z_][a-zA-Z0-9_]*);/\1/")

# if [ -z "$variables2" ]; then
#   echo "No matching patterns found."
#   exit 0
# fi
# echo "$variables2"

# # Pick a random line and save its line number and the variable it is equal to 
# varaible2=$(echo "$variables2" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')
# variableLine2=$(echo "$varaible2" | cut -d: -f1)
# variableName2=$(echo "$varaible2" | cut -d: -f2)

# # Delete the line
# sed -i -E "${variableLine2} s/uint64_t ${variableName} = [a-zA-Z_][a-zA-Z0-9_]*;//" "$file"

# # Whenever the pointer name is called, replace it with the variable it is equal to
# sed -i -E "s/${pointerName}/${variableName2}/g" "$file"
