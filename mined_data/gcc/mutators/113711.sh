#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

sed -i.bak -E 's#\[([^]]+)]\s*([a-zA-Z_][a-zA-Z_0-9]*|<<|>>|==|!=|<=|>=|&&|\|\||[-+*/%&|^<>])\s*#[\1 + 0x100] + #g' "$1" && rm -f "$1.bak"