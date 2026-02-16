#!/bin/bash

sed -i -E '
# Block 1: Find a typedef or a local variable declaration of a signed type.
/^\s*(typedef\s+)?(const\s+)?(schar|signed|char|short|int|long|long long)\b/ {
    # Exclude function definitions.
    /\)\s*\{/b

    # Change signed type to unsigned equivalent.
    s/\bsigned\s+long\s+long\b/unsigned long long/
    s/\blong\s+long\b/unsigned long long/
    s/\bsigned\s+long\b/unsigned long/
    s/\blong\b/unsigned long/
    s/\bsigned\s+short\b/unsigned short/
    s/\bshort\b/unsigned short/
    s/\bsigned\s+int\b/unsigned/
    s/\bint\b/unsigned/
    s/\bsigned\s+char\b/unsigned char/
    s/\bschar\b/unsigned char/
    s/\bchar\b/unsigned char/
    s/\bsigned\b/unsigned/

    # If it is a variable declaration with initialization, track the variable name.
    /=/ {
        h
        s/.*\b([a-zA-Z_][a-zA-Z0-9_]*)\s*=.*/\1/
        x
        b
    }

    # For typedefs or declarations without init, we are done with this line.
    b
}

# Block 2: Process subsequent lines for tracked variable usage.
x; /./!{x; b}
x;

/[?].*:/!b

G

s/^(.*\b([^\n]+)\b.*)\n\2$/\1/
t modify

s/\n.*//
b

:modify
s/\b([0-9]+)\b/\1U/g
x; s/.*//; x
' "$1"