#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
/unsigned _BitInt\([0-9]+\).*,.*_BitInt\([0-9]+\)|_BitInt\([0-9]+\).*,.*unsigned _BitInt\([0-9]+\)/{
  :a
  /}/!{
    $!{
      N
      ba
    }
  }

  :subst_loop

  # Case 1: (unsigned, signed). Only match if unsigned width is 1 or 2 digits (< 100).
  s/(unsigned _BitInt\([0-9]{1,2}\)\s+([a-zA-Z0-9_]+)\s*,\s*(_BitInt\([0-9]+\))\s+([a-zA-Z0-9_]+))((.|\n)*)([^a-zA-Z0-9_)])\b\2\b(\s*\/\s*)\b\4\b/\1\5\7(\3)\2\8\4/

  # Case 2: (signed, unsigned). Only match if unsigned width is 1 or 2 digits (< 100).
  s/((_BitInt\([0-9]+\))\s+([a-zA-Z0-9_]+)\s*,\s*(unsigned _BitInt\([0-9]{1,2}\))\s+([a-zA-Z0-9_]+))((.|\n)*)([^a-zA-Z0-9_)])\b\5\b(\s*\/\s*)\b\3\b/\1\6\8(\2)\5\9\3/

  t subst_loop
}
' "$file"