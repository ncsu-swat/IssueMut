#!/bin/bash

# This script removes preprocessor conditional directives (#if, #endif, etc.)
# surrounding the first function definition that is wrapped in such a block.
# It improves upon the original by ensuring that it only modifies blocks
# that actually contain a function definition and are simple conditional blocks,
# making it more robust.

# Ensure exactly one argument (the file to process) is provided.
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# These variables will hold the line numbers of the block to be modified.
start_del=""
end_del=""

# The script works in two stages:
# 1. An `awk` script identifies all top-level preprocessor blocks and prints their
#    start and end line numbers. It correctly handles nested directives.
# 2. A `while` loop reads these line numbers. For each block, it checks if
#    it contains a C-style function definition and is a "simple" block
#    (i.e., does not contain #else or #elif).
# 3. The first block that meets these criteria is targeted for modification.
#    The loop is then terminated.
#
# This approach is more accurate than a script that would modify
# the first preprocessor block regardless of its content or complexity.

# Process substitution `< <(...)` is used to prevent the `while` loop
# from running in a subshell, allowing variables set inside to persist.
while read -r start_line end_line; do
    # Extract the content of the block, excluding the #if and #endif lines.
    content=$(sed -n "$((start_line + 1)),$((end_line - 1))p" "$file")

    # FIX: Skip complex blocks containing #else or #elif. Removing the outer
    # #if/#endif would leave a dangling #else/#elif, causing a syntax error.
    if echo "$content" | grep -q -E '^[[:space:]]*#(else|elif)'; then
        continue
    fi

    # Use a heuristic to detect a function definition. We flatten the block's
    # content and search for the pattern `(...) {`, which is characteristic
    # of a C function definition signature, handling multi-line signatures.
    if echo "$content" | tr -d '\n' | grep -q -E '\([^)]*\)\s*\{'; then
        # Found the first suitable block. Store its line numbers.
        start_del=$start_line
        end_del=$end_line
        # Break the loop as we only want to modify the first one found.
        break
    fi
done < <(awk '
    # The pattern /#if/ correctly matches #if, #ifdef, and #ifndef.
    /^[[:space:]]*#if/ {
        if (nesting == 0) {
            start = NR;
        }
        nesting++;
    }
    /^[[:space:]]*#endif/ {
        if (nesting > 0) {
            nesting--;
            if (nesting == 0) {
                print start, NR;
            }
        }
    }
' "$file")

# If a suitable block was found, use sed to delete the directive lines.
if [ -n "$start_del" ]; then
    # The -i flag modifies the file in place. Two -e expressions are used
    # to perform two separate delete operations on the specific lines based
    # on their original line numbers.
    sed -i -e "${start_del}d" -e "${end_del}d" "$file"
fi