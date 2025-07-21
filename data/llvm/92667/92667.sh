#!/bin/bash

# The goal is to remove variable declarations that use `typeof` or `typeof_unqual`.
# The original script was faulty because it incorrectly assumed that such
# declarations would always appear at the beginning of a line (preceded only by
# optional whitespace). This assumption fails for declarations that include
# storage-class specifiers or type qualifiers, such as `extern` or `const`.
#
# For example, the original script's pattern `/^\s*\btypeof.../` would not match a line like:
#   extern typeof(p1) p1;
#
# The corrected script fixes this by removing the start-of-line anchor (`^`) and
# the leading whitespace matcher (`\s*`) from the regular expression. The new
# pattern `/\btypeof(_unqual)?\s*\(/` searches for the `typeof` or `typeof_unqual`
# keyword anywhere on the line. This makes the script more generic and robust,
# allowing it to correctly identify and remove these declarations even when they
# are preceded by other C keywords. The `s/.*//` command then deletes the entire
# line where the pattern is found, which is the action consistent with the
# provided test cases.

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# -i: Edit file in-place.
# -E: Use extended regular expressions.
# /\btypeof(_unqual)?\s*\(/ : This is the address. It matches any line that contains:
#   - \btypeof(_unqual)?: the whole word `typeof` or `typeof_unqual`.
#   - \s*\( : followed by optional whitespace and an opening parenthesis.
# This pattern is no longer anchored to the start of the line, making it more general.
# s/.*// : This is the command. It substitutes the entire matched line (.*)
#          with an empty string, effectively deleting the line.
sed -i -E '/\btypeof(_unqual)?\s*\(/s/.*//' "$file"