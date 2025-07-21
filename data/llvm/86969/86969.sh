#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script expands a C function with a single return of a negative constant
# into a multi-return switch statement.
#
# The original script was faulty because its filters for identifying a
# function definition were not robust enough. It could be fooled by
# parentheses inside multi-line comments, and it used non-portable `\s`
# shorthands for whitespace.
#
# The corrected script fixes these issues by:
# 1. Improving the comment filter to correctly identify lines inside a
#    C-style block comment (e.g., ` * ...`) without accidentally matching
#    pointer dereferences.
# 2. Using the portable `[[:space:]]` character class for all whitespace
#    matching, enhancing both robustness and portability.
#
# The overall logic remains:
# 1. Find a line that might be a function signature (contains `()`).
# 2. Apply a strict set of filters to weed out false positives.
# 3. If the line passes, buffer subsequent lines until a complete function
#    block (`{...}`) is in the pattern space.
# 4. Apply a regex substitution to replace the simple `return` with a `switch`
#    block, preserving the original return value as the first case.

sed -i -E '
# Heuristic: find a line that could be a function signature (contains parens).
/\)/ {
    # Filter out common false positives to avoid processing the wrong code.
    # Ignore lines ending in a semicolon (prototypes, function calls, etc.).
    /[[:space:]]*;[[:space:]]*$/b
    # Ignore control flow statements, return statements, and typedefs.
    /^[[:space:]]*(if|for|while|switch|return|typedef)[[:space:]]*\(/b
    # Ignore preprocessor directives.
    /^[[:space:]]*#/b
    # Ignore C/C++ style comments, including lines inside a block comment.
    # This is careful not to match pointer dereferences like `*p`.
    /^[[:space:]]*(\/\/|\/\*|\*([[:space:]]|\/|$))/b

    # If we get here, it is likely a function definition.
    # The following logic buffers the entire function body.

    # Label for a loop to find the opening brace.
    :a
    # If the block so far does not contain an opening brace...
    /\{/! {
        # ...and we are not at the end of the file, append the next line
        # and branch back to the loop start.
        $!{N; ba}
    }
    # Label for a loop to find the matching closing brace.
    # This simple loop assumes no nested braces in the target function body,
    # which is true for a function with only a single return statement.
    :b
    /\}/! {
        $!{N; bb}
    }

    # At this point, a complete function block should be in the pattern space.
    # Attempt to substitute it if it matches the simple return pattern.
    # \1: Captures the full function signature (potentially multi-line).
    # \2: Captures the original return statement body (e.g., "return -42").
    s~^(.+)[[:space:]]*\{[[:space:]]*(return[[:space:]]*-[0-9]+L?);[[:space:]]*\}[[:space:]]*$~\1 {\n  switch (rng()) {\n  case 1:\n    \2;\n  case 2:\n    return -160;\n  case 3:\n    return -168;\n  default:\n    return -172;\n  }\n}~
}' "$file"