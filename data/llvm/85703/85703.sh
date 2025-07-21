#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

file="$1"

# Apply transformations in-place
sed -i -E '
/^#define/!{
  # Apply only to lines that contain string literals
  /".*"/{
    # Replace prefixes with raw string literal forms
    s/\bu8"/u8R"/g
    s/\bu"/uR"/g
    s/\bL"/LR"/g
    s/\bU"/UR"/g

    # Add R after (void) if directly followed by a normal string
    s/([^R])"([^"]*)"/\1R"\2"/g
  }
}
' "$file"
