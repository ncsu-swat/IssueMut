#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

sed -i -E '
:a
$!N

# Attempt to substitute the first occurrence of a variable defined on the previous line.
# If successful, branch to a loop to handle subsequent occurrences on the same line.
# Backreferences: \1=L1+\n, \2=type, \3=var, \4=val, \5=pre-var, \6=post-var
s/^(\s*(.*\s+)([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^;]*);\s*\r?\n)(.*)\b\3\b(.*)/\1\5(\4)\6/
t loop

# If no substitution, print pattern space up to newline, delete it, and restart.
P
D
b a

:loop
# Loop to replace all other occurrences of the variable on the line.
s/^(\s*(.*\s+)([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^;]*);\s*\r?\n)(.*)\b\3\b(.*)/\1\5(\4)\6/
t loop

# After all substitutions, remove the now-unneeded variable definition line.
s/^\s*.*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*=\s*[^;]*;\s*\r?\n//

# Go back to the main loop to continue processing the rest of the file.
# The pattern space now holds the single modified line, and the N command in the
# main loop will append the next line to it.
b a
' "$file"