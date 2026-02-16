#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script uses GNU sed's -z flag to read the whole file into memory,
# allowing the regex to match across multiple lines.
#
# The original script had two main flaws that prevented it from matching the pattern:
# 1. `(^\s*)` at the beginning of the regex. With the -z flag, `^` only
#    matches the very beginning of the file, not the beginning of a line.
#    This was changed to `(\s*)` to correctly match any leading whitespace
#    (including newlines) before the `if` statement, thus preserving indentation.
# 2. The pattern for the function call in the `else` block was `\([^;]*\)`. This
#    is incorrect because it tries to match the call's closing parenthesis `)`
#    *after* matching `[^;]*`, which would have already consumed the `)`.
#    This was corrected to `\(([^)]*)\)` to properly match and capture the
#    arguments *inside* the parentheses of the callback function call.
#
# The corrected regex is as follows:
# - `(\s*)`: Captures leading whitespace/newlines for indentation (\1).
# - `if\s*\(([^)]+)\)`: Matches the if statement and captures the condition (\2).
# - `\s*\{?\s*`: Matches optional braces and whitespace.
# - `([_a-zA-Z0-9]+)`: Captures the dispatch function name (\3).
# - `\((.*),\s*([_a-zA-Z0-9]+)((,.*)?)?\)`: Captures the dispatch call's arguments:
#   - `(.*)`: Arguments before the callback (\4).
#   - `([_a-zA-Z0-9]+)`: The callback function name (\5).
#   - `((,.*)?)?`: Optional arguments after the callback, including the comma (\6).
# - `\s*;\s*\}?`: Matches the semicolon and optional closing brace.
# - `else\s*\{?\s*`: Matches the else part.
# - `\5\s*\(([^)]*)\)\s*;\s*\}?`: Matches the callback call in the else block, using a backreference to the callback name (\5) and correctly matching the arguments.
#
# The replacement string `\1\3_if(\4, \5, \2\6);` reassembles the captured parts into the desired single conditional function call.
sed -i -z -E 's/(\s*)if\s*\(([^)]+)\)\s*\{?\s*([_a-zA-Z0-9]+)\s*\((.*),\s*([_a-zA-Z0-9]+)((,.*)?)?\)\s*;\s*\}?\s*else\s*\{?\s*\5\s*\(([^)]*)\)\s*;\s*\}?/\1\3_if(\4, \5, \2\6);/g' "$file"