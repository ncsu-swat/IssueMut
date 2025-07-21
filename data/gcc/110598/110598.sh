#!/bin/bash
sed -i -E '
# Skip lines that are not the start of a function signature.
# Keywords like `struct`, `enum`, `union` are intentionally omitted from this
# list to allow for function definitions that return these types.
/^\s*(#|if|for|while|switch|do|return|goto|case|default|typedef|sizeof)\b/b

# A function signature must contain parentheses.
/\(/!b

# Start a loop to gather the full multi-line signature.
:gather

# If the pattern space ends with `);`, it is a function prototype or a
# function call statement, not a definition. Branch to end and print.
# This is more specific than just checking for `;` and correctly handles
# K&R-style parameter declarations.
/\)\s*;\s*$/b

# If an opening brace is found, we likely have the complete signature.
# Jump to the processing block.
/\{/b process

# If we are at the end of the file, we can a-t read more lines.
# Branch to end.
$b

# Append the next line to the pattern space and loop back to gather more.
N
b gather

:process
# Now we have a candidate function definition in the pattern space.

# Check if the attribute is already present. If so, do nothing.
/__attribute__\s*\(\s*\(\s*noipa\s*\)\s*\)/b

# All checks passed. This is a function definition without the attribute.
# Insert the attribute before the function signature.
i\
__attribute__((noipa))
' "$1"