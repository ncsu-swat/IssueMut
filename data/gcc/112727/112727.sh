#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

perl -i -0777 -pe 's/(\(\s*!\s*((?:[^()]+|\((?2)\))*)\s*\))(?! \s* \? \s* 1 \s* : \s* 0)/($1 ? 1 : 0)/g' "$file"