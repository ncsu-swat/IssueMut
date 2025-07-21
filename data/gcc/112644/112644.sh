#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E 's/(\b(typedef|void|char|short|long|float|double|struct|union|enum|const|static|volatile|unsigned|signed)\b[^;=\[]*\[)([2-9]|[1-9][0-9]+)(\])/\11\4/g' "$file"