#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED=$2

# Find all occurrences of "(void)"
matches=$(grep -noE '\(void\);' "$file")

# Check if matches are found
if [ -n"$matches" ]; then
  random_matches=$(echo "$matches" | awk -v seed="$SEED" '
  BEGIN {srand(seed); count=0}
{
    count++;
    lines[count] = $0;
}
END {
    if (count == 1) {
        print lines[1];
    } else if (count > 1) {
        idx1 = int(1 + rand() * count);
        do {
            idx2 = int(1 + rand() * count);
        } while (idx2 == idx1);  # Ensure idx2 is different from idx1
        
        print lines[idx1];
        print lines[idx2];
    }
}')

  line1=$(echo "$random_matches" | awk 'NR==1' | cut -d: -f1)
  line2=$(echo "$random_matches" | awk 'NR==2' | cut -d: -f1)

  sed -i -E "${line1}s/\(void\);/() = {};/" "$file"

  if [ -n "$line2" ]; then
    sed -i -E "${line2}s/\(void\);/() = {1};/" "$file"
  fi
fi