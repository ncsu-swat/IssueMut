#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

sed -i -E \
    -e 's/\bsigned\s+long\s+long\s+int\b/_BitInt(128)/g' \
    -e 's/\blong\s+long\s+int\b/_BitInt(128)/g' \
    -e 's/\bsigned\s+long\s+long\b/_BitInt(128)/g' \
    -e 's/\blong\s+long\b/_BitInt(128)/g' \
    -e 's/\bsigned\s+char\b/_BitInt(8)/g' \
    "$1"