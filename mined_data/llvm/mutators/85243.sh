#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script failed due to an overly complex and syntactically
# incorrect regular expression. The regex attempted to match a condition
# ("preceded by a blank line OR another enum") that did not align with the
# stated goal ("surrounded by blank lines").
#
# This corrected script simplifies the logic to match the actual goal.
# It retains the robust structure of the original script:
# 1. Slurp the entire file into pattern space for multi-line context.
# 2. Use a sentinel newline to handle matches at the start of the file.
# 3. Loop the substitution to handle consecutive matches.
#
# The key change is the substitution command, which now correctly and
# simply targets an enumerator line surrounded by blank lines. A blank
# line is defined as a line containing only horizontal whitespace.

sed -i -E '
  # Slurp the entire file into pattern space for multi-line matching.
  :a; N; $!ba;

  # Add a sentinel newline for uniform matching at the start of the file.
  s/^/\n/;

  # Loop to handle multiple, potentially consecutive, matches.
  :loop
  
  # Match an enum line with an assignment that is surrounded by blank lines.
  # The regex captures the necessary parts and removes the assignment (`=...`).
  # A blank line is a line containing only horizontal whitespace ([[:blank:]]).
  #
  # Regex Breakdown:
  # \1: (\n[[:blank:]]*\n)                   - The preceding blank line.
  # \2: ([[:blank:]]*[a-zA-Z_][a-zA-Z0-9_]*) - The enumerator identifier (to keep).
  #     [[:blank:]]*=[^,\n]*                 - The assignment part (to remove).
  # \3: ([[:blank:]]*,?[[:blank:]]*)         - Optional comma and space (to keep).
  # \4: (\n[[:blank:]]*\n)                   - The following blank line.
  s/(\n[[:blank:]]*\n)([[:blank:]]*[a-zA-Z_][a-zA-Z0-9_]*)[[:blank:]]*=[^,\n]*([[:blank:]]*,?[[:blank:]]*)(\n[[:blank:]]*\n)/\1\2\3\4/
  
  # If a substitution occurred, re-scan the entire buffer from the start.
  t loop

  # Remove the sentinel newline added at the beginning.
  s/^\n//;
' "$file"