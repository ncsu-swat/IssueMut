#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Skip lines that are not variable declarations, such as control flow,
# preprocessor directives, or function calls.
/^[[:space:]]*(#|goto|return|case|default|if|for|while|switch|else|do|typedef|struct|union|enum|extern|})\b/b

# Handle the first variable on a declaration line if it is uninitialized.
# This pattern is anchored to the start of the line (with optional whitespace)
# and will not match if an initializer `=` is present after the variable name.
s/^([[:space:]]+([a-zA-Z_][a-zA-Z0-9_<>*&:]+[[:space:]]+)+[*&[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*(\[[^]]*\])*)([[:space:]]*[,;])/\1 = 0\4/

# This loop handles subsequent uninitialized variables on the same line.
# It looks for a variable preceded by a comma and followed by a comma or semicolon.
# The `t a` command loops as long as a substitution is made, processing all
# such variables on the line. This part is not anchored to the start of the line,
# allowing it to find uninitialized variables that follow initialized ones.
:a
s/(,[[:space:]]*[*&[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*(\[[^]]*\])*)([[:space:]]*[,;])/\1 = 0\3/
t a
' "$file"