#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

original_content=$(<"$file")

# The fix is to make the LHS operand matching less greedy.
# The original `([^>]*)` could match past the closing parenthesis `)` of the
# if-condition, leading to catastrophic matching on complex files.
# By changing it to `([^>)]*)`, we prevent the match from crossing the `)`,
# effectively scoping the search for the operator within the if's condition.
# This introduces a limitation: the LHS expression cannot contain a ')' char,
# but this is a reasonable trade-off for robustness against incorrect greedy matching.

# Process braced if statements first
sed -i -zE \
    -e 's/if[[:space:]]*\(([^>)]*)[[:space:]]*>=[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 < \2);/g' \
    -e 's/if[[:space:]]*\(([^<)]*)[[:space:]]*<=[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 > \2);/g' \
    -e 's/if[[:space:]]*\(([^!)]*)[[:space:]]*!=[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 == \2);/g' \
    -e 's/if[[:space:]]*\(([^>)]*)[[:space:]]*>[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 <= \2);/g' \
    -e 's/if[[:space:]]*\(([^<)]*)[[:space:]]*<[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 >= \2);/g' \
    -e 's/if[[:space:]]*\(([^=)]*)[[:space:]]*==[[:space:]]*([^)]*)\)[[:space:]]*\{[[:space:]]*return[^;]*;[[:space:]]*\}/assert(\1 != \2);/g' \
    "$file"

# Process non-braced if statements
sed -i -zE \
    -e 's/if[[:space:]]*\(([^>)]*)[[:space:]]*>=[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 < \2);/g' \
    -e 's/if[[:space:]]*\(([^<)]*)[[:space:]]*<=[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 > \2);/g' \
    -e 's/if[[:space:]]*\(([^!)]*)[[:space:]]*!=[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 == \2);/g' \
    -e 's/if[[:space:]]*\(([^>)]*)[[:space:]]*>[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 <= \2);/g' \
    -e 's/if[[:space:]]*\(([^<)]*)[[:space:]]*<[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 >= \2);/g' \
    -e 's/if[[:space:]]*\(([^=)]*)[[:space:]]*==[[:space:]]*([^)]*)\)[[:space:]]*return[^;]*;/assert(\1 != \2);/g' \
    "$file"

new_content=$(<"$file")

if [ "$original_content" != "$new_content" ]; then
    if ! grep -q -E "^[[:space:]]*#include[[:space:]]+<assert\.h>" "$file"; then
        last_include_line=$(awk '/^[[:space:]]*#include/ { n=NR } END { print n }' "$file")
        if [ -z "$last_include_line" ]; then
            sed -i '1i#include <assert.h>' "$file"
        else
            sed -i "${last_include_line}a#include <assert.h>" "$file"
        fi
    fi
fi