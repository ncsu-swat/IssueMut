#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# First, handle literals that already have a fractional part.
# This includes cases with an empty fractional part like "0x9.".
# We append a "0" to the existing fractional part.
s/(0[xX][0-9a-fA-F]*\.[0-9a-fA-F]*)([pP][+-]?[0-9]+[[:alnum:]]*)/\10\2/g

# Second, handle literals that do not have a fractional part.
# We insert ".0" to create the fractional part.
# This rule will not match inputs that were already handled by the first rule,
# because those now contain a ".".
s/(0[xX][0-9a-fA-F]+)([pP][+-]?[0-9]+[[:alnum:]]*)/\1.0\2/g
' "$file"