#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script was faulty because the `n` command in sed, when used
# without the `-n` (no-autoprint) flag, prints the current pattern space
# before reading the next line. This caused the `#pragma omp taskwait` line
# to be printed immediately, making its subsequent removal impossible.
#
# This corrected script fixes the issue by adopting a more robust approach:
# 1. It uses `sed -n` to disable automatic printing, giving full control
#    over what gets printed and when.
# 2. It first deals with all lines that are NOT the target pragma using an
#    inverted address (`!`), printing them and skipping further processing.
# 3. When a target pragma is found, it's stored in the hold space (`h`).
# 4. A lookahead loop (`:a`) is used to read subsequent lines (`n`).
# 5. Blank lines are collected in the hold space (`H`) to handle cases
#    with empty lines between the pragma and the closing brace.
# 6. If the next non-blank line is a closing brace `}`, only the brace is
#    printed (`p`), effectively deleting the held pragma.
# 7. If the next non-blank line is any other statement, the held content
#    (pragma + blank lines) is retrieved (`g`), the new statement is
#    appended (`G`), and the combined block is printed. This preserves
#    the pragma when it's not the last statement.
# 8. The script handles the edge case of a pragma at the end of the file.

sed -n -E '
# Print any line that is NOT the target pragma and skip to the next line.
/^[[:space:]]*#pragma[[:space:]]+omp[[:space:]]+taskwait/!{
  p
  b
}

# If we are here, we found the pragma. Hold it.
h

# Start a loop to look ahead for the closing brace.
:a

# Handle end-of-file: if we hit EOF while looking ahead, the pragma
# was the last thing in the file. Print what we held and exit.
$ {
  g
  p
  d
}

# Read the next line into the pattern space.
n

# If the new line is blank, append it to the hold space and loop again.
/^[[:space:]]*$/{
  H
  b a
}

# If the new line is a closing brace, the pragma was the last statement.
# Print the brace, and the held pragma is implicitly discarded.
/^[[:space:]]*}[[:space:]]*$/{
  p
  b
}

# If we are here, the line was neither blank nor a brace. The pragma was
# NOT the last statement. Retrieve the held lines (pragma + any blanks),
# append the current line, and print the result.
g
G
p
' "$file" > "$file.tmp" && mv "$file.tmp" "$file"