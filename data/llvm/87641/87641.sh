#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"


# Transform _Generic(( → _Generic(+(
sed -i -E 's/_Generic\(/_Generic(+/g' "$file"


