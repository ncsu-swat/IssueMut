#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The logic is as follows:
# 1. Skip lines that start with a comment.
# 2. On other lines, check for the presence of 'static' and '['.
# 3. To distinguish array declarations from function calls/declarations,
#    ensure the line does NOT contain '('. This handles cases like
#    'static int func(int arr[])' or 'printf("... arr[0] ...")'.
# 4. If all conditions are met, it's likely a static array declaration.
#    Remove the 'static' keyword and the following whitespace.
sed -i -E '
/^[[:space:]]*(\/\/|\/\*)/b
/\bstatic\b/!b
/\[/!b
/\(/b
s/\bstatic\b[[:space:]]+//
' "$file"