#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
# Skip const variables
/\bconst\b/b
# Skip for loop initializers
/^\s*for\b/b

# Match lines that are likely variable declarations with an initializer
/^\s*(\b(static|extern|volatile|register|unsigned|signed)\b\s*)*\b(int|long|short|char|float|double)\b[^;]*=/ {
    # Remove scalar zero-initializers, like = 0, = 0.0, = NULL, = (0), etc.
    # This regex avoids aggregate initializers like = {0}.
    # The original script attempted to capture and replace the terminator (;,),
    # which was fragile. This version simply removes the initializer part,
    # leaving the terminator untouched, which is more robust.
    # A latent bug with '\''\0'\'' (which sed interprets as a backreference) is
    # also fixed to be '\''\\0'\''.
    s/\s*=\s*(\(\s*0\s*\)|'\''\\0'\''|(0\.0*|\.0+)[fFlL]?|0[xX]0+|NULL|0[uUlL]*)\b//g
}
' "$file"