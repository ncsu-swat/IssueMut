#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Read the whole file into the pattern space, replacing newlines with a temporary marker
:a
N
$!ba
s/\n/\x07/g

# Replace statement-terminating semicolons with a temporary marker to avoid
# matching semicolons inside return expressions. This is a simplification
# that works for the given test cases.
s/;/§/g

# Pass 1: Normalize braced `if` blocks.
# `if (...) { return ...; }` becomes `if (...) return ...;`
# This simplifies the structure by removing the braces around the `if`s return statement.
s#(if[ \t]*\([^)]*\))[ \t\x07]*\{[ \t\x07]*(return[ \t]+[^§]*§)[ \t\x07]*\}#\1 \2#g

# Pass 2: Normalize braced `else` blocks.
# `else { return ...; }` becomes `else return ...;`
# This simplifies the structure by removing the braces around the `else`s return statement.
s#(else)[ \t\x07]*\{[ \t\x07]*(return[ \t]+[^§]*§)[ \t\x07]*\}#\1 \2#g

# Pass 3: Transform the normalized `if-else` structure into a ternary operator.
# By now, all relevant blocks look like `if (...) return ...; else return ...;`
s#([ \t]*)if[ \t]*\(([^)]*)\)[ \t\x07]*return[ \t]+([^§]*)§[ \t\x07]*else[ \t\x07]*return[ \t]+([^§]*)§#\1return \2 ? \3 : \4§#g

# Restore the original semicolons and newlines
s/§/;/g
s/\x07/\n/g
' "$file"