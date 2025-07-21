#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script uses GNU sed features:
# -i: edit in-place
# -z: treat the entire file as a single, null-terminated line. This allows
#     regex to match across newlines, which is essential for matching the
#     multi-line attribute and function declaration.
# -E: use extended regular expressions for cleaner syntax.
#
# The logic uses a loop (:peel, t peel) to handle an arbitrary number of clones.
#
# 1. The first 's' command finds a 'target_clones' attribute with at least two
#    entries (indicated by the presence of a comma). It "peels off" the first
#    clone into a 'target_version' declaration and rewrites the 'target_clones'
#    attribute with the remaining clones.
#
# 2. The 't peel' command branches back to the ':peel' label if the first
#    substitution was successful, effectively creating a loop that processes
#    one clone at a time.
#
# 3. When no more commas are found, the first 's' command fails, the 't' command
#    does not branch, and execution falls through to the second 's' command.
#
# 4. The second 's' command is the base case. It finds 'target_clones' attributes
#    with only a single entry and converts them to the final 'target_version'
#    declaration. The 'g' flag ensures all such instances are converted.
#
# Key fixes from the original script:
# - The second 's' command now correctly captures and re-appends the function
#   declaration, which was previously being dropped.
# - Corrected the back-reference bug ('\2' was used where there was only one
#   capture group in the original second command's pattern).
# - Made the pattern for capturing the function declaration more robust ([^;]+;).

sed -i -z -E '
:peel
# Match a target_clones with a comma, indicating multiple clones remain.
# Capture groups:
# \1: The entire __attribute__((...)) block
# \2: The content of the first quoted clone string
# \3: The remaining part of the argument list (including other clones)
# \4: The function declaration, including leading whitespace and trailing semicolon
s/(__attribute__\(\(target_clones\("([^"]+)",[[:space:]]*(.*)\)\)\))([[:space:]]*[^;]+;)/__attribute__((target_version("\2")))\4\n\n__attribute__((target_clones(\3)))\4/
# If the substitution succeeded, loop back to peel the next one.
t peel

# Base case: Match a target_clones with only one clone left (no comma).
# Capture groups:
# \1: The entire __attribute__((...)) block
# \2: The content of the single quoted clone string
# \3: The function declaration
s/(__attribute__\(\(target_clones\("([^"]+)"\)\)\))([[:space:]]*[^;]+;)/__attribute__((target_version("\2")))\3/g
' "$file"