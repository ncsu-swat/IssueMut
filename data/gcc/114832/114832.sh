#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

tmpfile=$(mktemp)
trap 'rm -f "$tmpfile"' EXIT

# The original script failed because the sed expression was in double quotes,
# causing the shell to incorrectly interpret backslashed characters. Also,
# literal curly braces were not escaped, which is required in ERE.
#
# The corrected script uses single quotes to prevent shell interpretation and
# escapes the curly braces `\{` and `\}`.
#
# The regex logic is as follows:
# 1. Address matcher `/\b(type|...|for)\b/`: Only process lines containing a type keyword or 'for'.
# 2. Substitution `s/search/replace/`:
#    - `search`: Matches a variable declaration and its initializer.
#      - `(\**\s*[a-zA-Z_][a-zA-Z0-9_]*\s*(\[[^]]*\])*)`: Captures the variable part (group 1), including pointers (*) and array brackets ([]).
#      - `\s*=\s*`: Matches the assignment operator.
#      - `(\{[^}]*\}|[^,;)]+)`: Matches the initializer, either a brace-enclosed list or a sequence of characters that are not ',', ';', or ')'.
#    - `replace`: `\1` replaces the entire match with only the captured variable part, effectively removing the initializer.
if sed -E '/\b(int|long|short|char|float|double|void|signed|unsigned|const|_Bool|struct|union|enum|for)\b/s/(\**\s*[a-zA-Z_][a-zA-Z0-9_]*\s*(\[[^]]*\])*)\s*=\s*(\{[^}]*\}|[^,;)]+)/\1/' "$file" > "$tmpfile"; then
    mv "$tmpfile" "$file"
else
    exit 1
fi