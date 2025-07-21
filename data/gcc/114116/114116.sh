#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -n -E '
# This script uses a state machine, with the state stored in the hold space.
# State "" (empty string): We are outside a function.
# State "1": We are inside a function, looking for the first statement.

# Swap pattern space and hold space to check the state.
x
# Check if we are NOT in state "1".
/^1$/!{
  # We are in the "outside" state. Swap back.
  x
  # Look for a line containing an opening brace.
  /\{/ {
    # If the line is not a control structure or type definition,
    # assume it is a function definition.
    /^[ \t]*(if|for|while|switch|else|typedef|struct|union|enum)\b/! {
      # Print the function definition line.
      p
      # Switch to state "1" by putting "1" in the hold space.
      s/.*/1/
      h
      # End this cycle.
      b
    }
  }
  # If we are "outside" and did not find a function start, just print the line.
  p
  b
}

# If we reached here, we are in state "1".
# Swap back the pattern space.
x
# Skip blank lines and comments, while staying in state "1".
/^[ \t]*($|\/\/|\/\*|#)/ {
  p
  b
}

# This is the first non-comment, non-blank line.
# This is the target statement. Remove "static" from the beginning.
s/^[ \t]*static[ \t]+//
p

# We have modified the first statement. Now, reset to the "outside" state.
g
s/.*//
h
# End this cycle. Subsequent lines will be handled by the "outside" logic.
b
' "$file"