#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^[[:space:]]*\bstatic\b/ {
    /\bconstexpr\b/b
    /;\s*(\/\/.*)?$/!b
    # The original check for an initializer was too broad and could match
    # non-constant expressions like function calls. This refined check
    # looks for literals or brace initializers, which are more likely to
    # be constant expressions, making the script safer to run on complex code.
    /(=[[:space:]]*([-.0-9]+(f|L|u|ul|ull)?|0x[0-9a-fA-F]+|"[^"]*"|'\''[^'\'']'\''|true|false|nullptr)|\{[^}]*\})/ {
        s/\bstatic\b/static constexpr/
    }
}' "$file"