#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script failed due to a syntax error in the first sed expression.
# The `addr1{addr2!cmd}` construct can be problematic for some sed parsers.
# This script fixes the issue by using a more standard and robust conditional
# branching (`b`) command. It also improves the regular expressions to be more
# precise and handle a wider range of C function signatures correctly.

sed -i -E \
    -e '
        # Goal 1: Add `ownership_returns` to a void function.
        # We match void functions, then branch (skip) if the attribute is already present.
        # Otherwise, we add the attribute before the trailing semicolon or opening brace.
        /^void\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(.*\)/{
            /ownership_returns/b
            s/\)(\s*([;{]|$))$/) __attribute__((ownership_returns(foo)))\1/
        }
    ' \
    -e '
        # Goal 2: Remove pointer from a function with `ownership_returns`.
        # We match lines with the attribute, then use substitution to remove the first `*`
        # found between the return type and the function name.
        /ownership_returns/s/^([a-zA-Z_][a-zA-Z0-9_ \t]*[a-zA-Z0-9_])\s*\*\s*([a-zA-Z_][a-zA-Z0-9_]*\s*\(.*)/\1 \2/
    ' \
    "$file"