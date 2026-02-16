#!/bin/bash
sed -i -E '
# Heuristically identify a line that could be a function signature.
# It should start with type/qualifier words, have a name, and parentheses.
/^\s*([a-zA-Z_]\w*\s+)+[\w\s\*&]*\w+\s*\(/!b

# Exclude common keywords that can be mistaken for functions, and main.
/^\s*(if|for|while|switch|sizeof|return|typedef|struct|union|enum)\b/b
/\bmain\s*\(/b

# This is a candidate signature. It might span multiple lines.
# We accumulate lines into the pattern space until we find the
# end of the signature, marked by a `{` or `;`.
:slurp
/[{;]/!{
    $!N
    b slurp
}

# Now the pattern space holds a complete function signature.
# If it already contains the `noipa` attribute, do nothing.
/\bnoipa\b/b

# If we reach here, the signature does not have `noipa`. We must add it.
# First, try to merge with an existing __attribute__ clause.
# If successful, branch to the end of the script for this cycle.
s/(__attribute__\s*\(\()/\1noipa, /
t

# If no __attribute__ clause existed, add a new one.
# The slurping logic ensures the first `{` or `;` in the pattern space
# is the end of the signature header. We insert the attribute before it,
# preserving any whitespace.
s/(\s*)([;{])/ __attribute__((noipa))\1\2/
' "$1"