#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Slurp the entire file into the pattern space to enable multi-line matching.
H;1h;$!d;x

# Start a loop to find and combine all occurrences of the pattern.
:combine_loop
# This substitution finds the two-step assignment pattern.
# It is made robust to handle multiple newlines/blank lines between statements.
#
# Regex breakdown:
# ([[:space:]]*)          - \1: Indentation of the first line.
# (\w+)                    - \2: The pointer variable name.
# \s*=\s*&                 - The assignment of an address.
# ([^;]+)                  - \3: The array access expression.
# ;                        - End of the first statement.
# (([[:space:]]*\n)+[[:space:]]*) - \4: Whitespace/newlines between statements (one or more lines).
# (\w+)                    - \6: The target variable for the final value.
# \s*=\s*\*\s*\b\2\b;      - The dereference assignment, using a backreference (\2)
#                            with word boundaries to ensure it is the same pointer.
#
# Replacement breakdown:
# \1##DELETE_LINE##        - Mark the first assignment line for deletion.
# \4                       - Preserve the spacing between the original lines.
# \6 = \3;                 - Construct the new, direct assignment line.
# ##PTR_TO_DELETE##\2      - Add a marker with the pointer name for later removal
#                            of its declaration.
s/([[:space:]]*)(\w+)\s*=\s*&([^;]+);(([[:space:]]*\n)+[[:space:]]*)(\w+)\s*=\s*\*\s*\b\2\b;/\1##DELETE_LINE##\4\6 = \3;##PTR_TO_DELETE##\2/
# If a substitution occurred, loop back to find more.
t combine_loop

# Remove the marked lines from the first step of the assignment.
s/[^\n]*##DELETE_LINE##\n?//g

# Start a loop to clean up the declarations of the temporary pointers.
:cleanup_loop
# If no more pointer markers are left, exit the loop.
/##PTR_TO_DELETE##/!b

# To process one pointer at a time, change its marker to a "processing" state.
s/##PTR_TO_DELETE##(\w+)/##PROCESSING##\1/

# Find the declaration of the pointer currently being processed and remove it.
# This regex is more robust to handle qualifiers (e.g., const).
#
# Regex breakdown:
# (\n[[:space:]]*[^\n;]*\*\s*[^;]*\b(\w+)\b[^;]*;) - \1: The full declaration line.
#   [^\n;]*\*                               - Matches the type and the pointer asterisk.
#   [^;]*\b(\w+)\b[^;]*                      - Matches the pointer name (\2) allowing for
#                                              qualifiers around it (e.g. `* const ptr`).
# (.*)                                    - \3: All content between the declaration and our marker.
# ##PROCESSING##\2                        - The marker, with a backreference to ensure we delete
#                                           the declaration for the correct pointer.
#
# Replacement:
# \3                                      - Replaces the entire match with just the content
#                                           in between, effectively deleting the declaration
#                                           line and the processing marker.
s/(\n[[:space:]]*[^\n;]*\*\s*[^;]*\b(\w+)\b[^;]*;)(.*)##PROCESSING##\2/\3/
# If a declaration was successfully removed, loop back to find more pointers to clean up.
t cleanup_loop

# If the declaration was not found, the ##PROCESSING## marker remains.
# Remove it to prevent an infinite loop, then continue the cleanup process.
s/##PROCESSING##\w+//
b cleanup_loop

' "$file"