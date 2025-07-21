#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"

sed -i -E 's/inline [a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\([a-zA-Z_][a-zA-Z0-9_]* ([a-zA-Z_][a-zA-Z0-9_]*)\) \{ return (.*); \}/#define \1(\2) (\3)/' "$file"