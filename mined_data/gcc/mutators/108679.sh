#!/bin/bash

sed -i -E '
# Address to find the start of a struct definition.
# It handles optional typedefs and struct tags.
/(^|[^a-zA-Z0-9_])(typedef[[:space:]]+)?struct[^{]*\{/ {
    # Label for a loop to slurp all lines of a multi-line struct.
    :slurp
    # If the pattern space does not contain the end of the struct `};`,
    # append the next line and loop back.
    /\}.*;/!{
        $!N
        b slurp
    }

    # Label for a loop to delete fields one by one.
    :del_loop
    # This substitution finds the first two fields and removes the second one.
    # Group 1: Matches from `{` up to the first `;`. This is the first field, which we keep.
    # Group 2: Matches the second field, from after the first `;` to the second `;`. This is deleted.
    # Group 3: Matches the closing brace and the rest of the definition. This is kept.
    # The substitution replaces the pattern with just groups 1 and 3.
    s/(\{[^;]*;)([^;]*;)(\s*\}.*)/\1\3/
    # The `t` command branches to :del_loop if the substitution was successful.
    # This creates a loop that continues until no more fields can be deleted,
    # which happens when only one field (and one semicolon) is left.
    t del_loop
}' "$1"