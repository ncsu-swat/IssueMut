#!/bin/bash
sed -i -E '
  # Slurp the entire file to handle multi-line matches
  :a; N; $!ba;

  # Find a "#pragma GCC unroll 0" line, followed by optional blank lines,
  # followed by a loop keyword (for, while, do).
  # If found, remove the pragma line, keeping the blank lines and the loop.
  #
  # Breakdown of the regex:
  # ([ \t]*#pragma GCC unroll 0\n)  - Group 1: The pragma line.
  # (([ \t]*\n)*)                  - Group 2: Optional blank lines between pragma and loop.
  # ([ \t]*(for|while|do)\b)       - Group 4: The start of the loop line (indentation and keyword).
  #
  # The replacement `\2\4` effectively deletes the pragma line (Group 1) while
  # preserving the blank lines (Group 2) and the loop line (Group 4 starts it).
  # The "g" flag handles multiple occurrences in the file.
  s/([ \t]*#pragma GCC unroll 0\n)(([ \t]*\n)*)([ \t]*(for|while|do)\b)/\2\4/g
' "$1"