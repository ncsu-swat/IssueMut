#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The script identifies a three-step accumulation pattern:
# 1. A temporary variable is declared.
#    (e.g., int temp_total;)
# 2. The temporary variable is assigned the result of a function call, where an accumulator variable is one of the arguments.
#    (e.g., temp_total = add_and_double(data[i], total);)
# 3. The accumulator is updated with the value of the temporary variable.
#    (e.g., total = temp_total;)
#
# The script then collapses these three steps into a single direct assignment to the accumulator.
#    (e.g., total = add_and_double(data[i], total);)
#
# Regex Breakdown:
# ([ \t]*)                                      # \1: Leading indentation of the block.
# ([^\n]*[^ \t])                                 # \2: The type of the temporary variable.
# [ \t]+                                         # Space(s) between type and variable name.
# ([a-zA-Z_][a-zA-Z0-9_]*)                       # \3: The temporary variable's name.
# ;                                              # End of declaration.
# (\s*\n\s*)                                     # \4: Whitespace, including at least one newline, between statements.
# \3\s*=\s*                                      # Assignment to the temporary variable (using backreference \3).
# (                                              # \5: The right-hand side of the assignment (the function call).
#   .*\b([a-zA-Z_][a-zA-Z0-9_]*)\b.*             # This captures the function call, and crucially, also captures...
#                                                # \6: ...the accumulator variable's name from within the function call's arguments.
# )                                              # End of RHS capture.
# ;                                              # End of first assignment.
# (\s*\n\s*)                                     # \7: Whitespace, including at least one newline, between statements.
# \6\s*=\s*\3;                                   # The final assignment, verifying that the accumulator (\6) is assigned the temporary (\3).
#
# Replacement:
# \1\6 = \5;                                     # Reconstruct the line as: <indent><accumulator> = <function_call>;
#
# This approach is robust because it explicitly finds the accumulator variable (\6) inside the function call arguments
# and then verifies that this same variable is the one being updated in the third step. This avoids incorrect transformations.
sed -i -E -z 's/([ \t]*)([^\n]*[^ \t])[ \t]+([a-zA-Z_][a-zA-Z0-9_]*);(\s*\n\s*)\3\s*=\s*(.*\b([a-zA-Z_][a-zA-Z0-9_]*)\b.*);(\s*\n\s*)\6\s*=\s*\3;/\1\6 = \5;/g' "$file"