#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/^\s*(static|const|extern|volatile|auto|register|signed|unsigned|struct|union|enum|void|char|short|int|long|float|double|bool|_Bool)\b/!b

h

:s1
s/("[^",]*),([^"]*")/\1\x01\2/g
t s1
:p1
s/\(([^,)]*),([^)]*)\)/\(\1\x01\2\)/g
t p1
:b1
s/\{([^,}]*),([^}]*)\}/\{\1\x01\2\}/g
t b1

/.*,.*=.*/!{
    g
    b
}

g

:s2
s/("[^",]*),([^"]*")/\1\x01\2/g
t s2
:p2
s/\(([^,)]*),([^)]*)\)/\(\1\x01\2\)/g
t p2
:b2
s/\{([^,}]*),([^}]*)\}/\{\1\x01\2\}/g
t b2

s/[[:space:]]*=[^,;]*//g

s/\x01/,/g
' "$file"