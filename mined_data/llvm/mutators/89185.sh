#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script `s/(.*)\bvoid\b(\s*\*.*=.*&&.*)/\1char\2/` was faulty.
# It incorrectly assumed that the pointer's asterisk `*` would immediately
# follow the `void` type specifier (and any whitespace). This fails for
# declarations where type qualifiers appear between `void` and `*`, such as
# `void const * p = &&label;`.
#
# The corrected regex `s/(.*)\bvoid\b(\s*.*\*.*=.*&&.*)/\1char\2/` fixes this.
# - `(.*)\bvoid\b` captures any preceding code and matches the `void` keyword.
#   The greediness of `(.*)` ensures that if multiple `void` keywords exist on
#   a line, the last one that satisfies the full pattern is chosen, which is
#   typically correct for multi-declaration lines.
# - `(\s*.*\*.*=.*&&.*)` is the main change.
#   - `\s*.*\*` now correctly matches the pointer declaration part by allowing
#     any characters (`.*`) between the optional whitespace (`\s*`) after `void`
#     and the asterisk `\*`. This handles any type qualifiers like `const` or
#     `volatile` placed after the base type.
#   - The rest of the pattern, `.*=.*&&.*`, ensures we only match declarations
#     that are initialized with a label address (`&&`).
# - The replacement `\1char\2` substitutes `void` with `char` while preserving
#   all other parts of the line, including qualifiers and surrounding code.
sed -i -E 's/(.*)\bvoid\b(\s*.*\*.*=.*&&.*)/\1char\2/' "$file"