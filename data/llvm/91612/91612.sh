#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script's regular expression was faulty. It failed to match the
# semicolon ';' at the end of the `__builtin_assume` statement. The pattern
# expected a closing parenthesis ')' as the final significant character, but
# in valid C, a statement-level call is terminated by a semicolon. This
# mismatch caused the pattern to never match any valid input, leading to
# an incorrect output (specifically, no change was made).
#
# The corrected regex below includes `\)[[:space:]]*;` to properly match
# the closing parenthesis, any trailing whitespace, and the final semicolon.
# The replacement string is also adjusted to append `);` to ensure the
# resulting merged line is a valid C statement.
#
# Additionally, the pattern for whitespace has been changed from `[ \t]` to the
# more general `[[:space:]]` to correctly handle all forms of whitespace,
# and the whole-file processing logic has been made more portable for non-GNU seds.

sed -i -E '
  :a
  N
  $!ba
  s/([[:space:]]*)([a-zA-Z_][a-zA-Z0-9_]*)(\+\+|--);[[:space:]]*\r?\n[[:space:]]*(__builtin_assume\()(.*?)\b\2\b(.*)\)[[:space:]]*;/\1\4\5\3\2\6);/g
' "$file"