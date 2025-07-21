#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script used a single, complex regular expression with optional
# brace matching (`\{?` and `\}?`) to handle both braced and non-braced
# if-else statements. This approach is fragile because the optional markers for
# the opening and closing braces are independent, and the broad `[[:space:]]*`
# can lead to unexpected non-matches when combined with many optional parts.
# The script failed because the regex did not match all valid cases.
#
# The corrected script resolves this by breaking the problem into distinct,
# well-defined syntactic cases and handling them with separate sed commands.
# This makes the matching for each case explicit and robust.
#
# We use four commands to cover all combinations of braced and non-braced
# `if` and `else` blocks:
# 1. Braced `if`, Braced `else`
# 2. Braced `if`, Non-braced `else`
# 3. Non-braced `if`, Braced `else`
# 4. Non-braced `if`, Non-braced `else`
#
# Each regex uses `([^;]*)` to capture the return value, which correctly
# handles complex expressions as long as they don't contain semicolons.
# The `-z` flag allows matching across newlines, and the capture groups
# `\1` (line start), `\2` (indentation), `\3` (condition), `\4` (true value),
# and `\5` (false value) are used to construct the ternary expression.

# Case 1: if { ... } else { ... }
sed -i -E -z 's/(^|\n)([ \t]*)if[[:space:]]*\((.*)\)[[:space:]]*\{[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*\}[[:space:]]*else[[:space:]]*\{[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*\}/\1\2return (\3 ? \4 : \5);/g' "$file"

# Case 2: if { ... } else return ...;
sed -i -E -z 's/(^|\n)([ \t]*)if[[:space:]]*\((.*)\)[[:space:]]*\{[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*\}[[:space:]]*else[[:space:]]*return[[:space:]]+([^;]*);/\1\2return (\3 ? \4 : \5);/g' "$file"

# Case 3: if (...) return ...; else { ... }
sed -i -E -z 's/(^|\n)([ \t]*)if[[:space:]]*\((.*)\)[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*else[[:space:]]*\{[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*\}/\1\2return (\3 ? \4 : \5);/g' "$file"

# Case 4: if (...) return ...; else return ...;
sed -i -E -z 's/(^|\n)([ \t]*)if[[:space:]]*\((.*)\)[[:space:]]*return[[:space:]]+([^;]*);[[:space:]]*else[[:space:]]*return[[:space:]]+([^;]*);/\1\2return (\3 ? \4 : \5);/g' "$file"