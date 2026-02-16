#!/bin/bash

sed -i -E '
  # Read the whole file into pattern space to allow multi-line matching
  :a; N; $!ba;
  # Loop to apply transformations repeatedly until no more matches are found
  :b

  # Case 1: Braced continue: if (!cond) { continue; } action;
  # This pattern is made more specific by matching the action as a single line `([ \t]*[^\n]*)`
  # to prevent the original script'"'"'s bug of greedily consuming following lines (e.g., a loop'"'"'s closing brace).
  # \1: if-indent, \3/\4: condition, \5: rest of if-line, \6: brace-indent, \7: action-line
  s/([ \t]*)if\s*\(\s*!\s*(\((.*)\)|([^\s(].*))\s*\)([^\n]*)\n([ \t]*)\{\s*\n[ \t]*continue;[^\n]*\n\6\}[ \t]*\n([ \t]*[^\n]*)/\1if (\3\4)\5\n\7/
  t b

  # Case 2: Unbraced continue: if (!cond) continue; action;
  # Same fix as above to make the action match non-greedy across lines.
  # \1: if-indent, \3/\4: condition, \5: rest of if-line, \6: action-line
  s/([ \t]*)if\s*\(\s*!\s*(\((.*)\)|([^\s(].*))\s*\)([^\n]*)\n[ \t]*continue;[^\n]*\n([ \t]*[^\n]*)/\1if (\3\4)\5\n\6/
  t b
' "$1"