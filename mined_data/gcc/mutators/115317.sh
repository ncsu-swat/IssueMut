#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
  # For each function type, first check if it is a declaration.
  # If so, `s/pattern/&/` succeeds, and `t` branches past the transformation.
  # Otherwise, perform the transformation using a temporary marker in the name
  # to prevent the `g` flag from causing recursive replacements.

  s/(\bisinff\s*\(\s*float\s*\))/\1/; t isinff_done
  s/\b(isinff)\(([^)]+)\)/(\2 < 0.0f ? -__\1__(\2) : __\1__(\2))/g
  :isinff_done

  s/(\bisinfl\s*\(\s*long double\s*\))/\1/; t isinfl_done
  s/\b(isinfl)\(([^)]+)\)/(\2 < 0.0L ? -__\1__(\2) : __\1__(\2))/g
  :isinfl_done

  s/(\bisinf\s*\(\s*double\s*\))/\1/; t isinf_done
  s/\b(isinf)\(([^)]+)\)/(\2 < 0.0 ? -__\1__(\2) : __\1__(\2))/g
  :isinf_done

  # After all potential transformations, remove the markers to restore
  # the original function names in the replacement expressions.
  s/__isinff__/isinff/g
  s/__isinfl__/isinfl/g
  s/__isinf__/isinf/g
' "$file"