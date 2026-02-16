#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script refactors a C for-loop by moving a single statement from its
# body into the loop's update clause. It uses a multi-line processing
# technique in sed for robustness.
#
# How it works:
# 1. A sed address range `/for...{/,/}/` is used to identify and isolate
#    for-loop blocks. This is generally more reliable than using an N-P-D loop.
# 2. Inside this range, `H` appends each line to the hold space, accumulating
#    the entire block.
# 3. When the end of the range (a line with `}`) is found, `g` replaces the
#    pattern space with the accumulated block from the hold space.
# 4. A leading newline (an artifact of the `H` command) is removed.
# 5. Two main substitution commands (`s/.../.../`) handle the transformation.
#    - The first one handles loops that already have an update clause. It moves
#      the body statement before the existing clause, separated by a comma.
#    - The second one handles loops with an empty update clause, moving the
#      body statement to become the new update clause.
#    - A `t` command is used to branch to the end if the first substitution
#      is successful, preventing the second one from being attempted.
# 6. The regular expressions are crafted to be precise:
#    - They expect the loop body to be on a new line after the opening brace.
#    - The statement is captured using `([^;]*[^[:space:]])`. This pattern
#      matches a sequence of non-semicolon characters that ends with a
#      non-whitespace character, effectively capturing the statement while
#      trimming surrounding whitespace on its line.
# 7. After a successful transformation, `p` prints the modified loop. The hold
#    and pattern spaces are then cleared to prevent sed's default output
#    from printing the original lines again.
# 8. The `d` command deletes the original lines of the processed block.
# 9. Any code outside the targeted for-loop structure is unaffected and
#    printed by default.

sed -i -E '
/for[[:space:]]*\([^)]*\)[[:space:]]*\{/,/\}/ {
    H
    /}/ {
        g
        s/^\n//

        # Case 1: Non-empty update clause.
        # Moves body statement, adding it with a comma before the existing update clause.
        # The statement is captured by group \5.
        s/^([[:space:]]*)for[[:space:]]*\(([^;]*);([^;]*);(.*[^[:space:]].*)\)[[:space:]]*\{[[:space:]]*\n[[:space:]]*([^;]*[^[:space:]])[[:space:]]*;[[:space:]]*\n?[[:space:]]*\}/\1for (\2; \3; \5, \4) {}/
        t done

        # Case 2: Empty update clause.
        # Moves body statement to become the new update clause.
        # The statement is captured by group \4.
        s/^([[:space:]]*)for[[:space:]]*\(([^;]*);([^;]*);[[:space:]]*\)[[:space:]]*\{[[:space:]]*\n[[:space:]]*([^;]*[^[:space:]])[[:space:]]*;[[:space:]]*\n?[[:space:]]*\}/\1for (\2; \3; \4) {}/

        :done
        p
        s/.*//; h
    }
    d
}
' "$file"