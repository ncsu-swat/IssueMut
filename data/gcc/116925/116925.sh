#!/bin/bash
sed -i -E '
N
s/^[[:space:]]*(.*[[:space:]]+)([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*=[[:space:]]*([^;]+);[[:space:]]*\n(.*?)\b\2\b(.*?)\b\2\b(.*)/\4\3\5\3\6/
P
D
' "$1"