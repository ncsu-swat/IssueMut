#!/bin/bash

# This script removes the 'allocate' clause from OpenMP pragmas in a given file.
# It is designed to be robust against various formatting, including multi-line
# pragmas and clauses with nested parentheses.

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The sed script operates as follows:
# 1. It identifies OpenMP pragma lines and joins any continued lines (those ending with '\').
# 2. If a pragma contains an 'allocate' clause, it enters a loop to remove it.
# 3. The loop is designed to handle 'allocate' clauses with nested parentheses.
# 4. The loop first attempts to remove the 'allocate' clause directly, if its
#    argument contains no nested parentheses. If successful, the script branches
#    to a cleanup stage and is done with the line.
# 5. If direct removal fails, it means the clause's arguments contain nested
#    parentheses. The script then "simplifies" the clause by finding the first
#    innermost pair of parentheses '(...)' *within* the 'allocate' clause and
#    replacing it with a placeholder '[]'. This simplification is targeted and
#    does not affect other clauses.
# 6. After a successful simplification, the script loops back to step 4. This
#    process repeats until the 'allocate' clause is simplified enough to be
#    removed by the direct removal pattern.
# 7. If a simplification step fails to change the line, the script exits the
#    loop for that pragma, preventing an infinite loop on malformed input.
# 8. Finally, it cleans up any extra whitespace resulting from the removal.

sed -i -E '
/^[[:space:]]*#pragma[[:space:]]+omp/ {
  # Join continued lines (ending with \)
  :join
  /\\$/ {
    N
    s/\\\n[[:space:]]*/ /
    b join
  }

  # Process only if an allocate clause exists. If not, branch to end of block.
  /\b[aA][lL][lL][oO][cC][aA][tT][eE]\b/!b

  # Loop to simplify and remove the clause.
  :remove_loop
  # Attempt to remove the allocate clause if it is simple (no nested parentheses).
  # If successful, branch to cleanup.
  s/[[:space:]]*\b[aA][lL][lL][oO][cC][aA][tT][eE]\b[[:space:]]*\(([^()]*)\)//; t cleanup

  # If removal failed, simplify the clause by replacing the first innermost
  # parenthesis group inside it with a placeholder. Then, loop back.
  # This is anchored to the "allocate" keyword to avoid modifying other clauses.
  s/(\b[aA][lL][lL][oO][cC][aA][tT][eE]\b[[:space:]]*\([^()]*)\(([^()]*)\)/\1[]/; t remove_loop

  # If we reach here, removal and simplification both failed.
  # This can happen with malformed pragmas (e.g., mismatched parentheses).
  # We exit the block for this line to avoid an infinite loop.
  b

  :cleanup
  # Clean up any extra whitespace that may result from the removal.
  s/[[:space:]]{2,}/ /g
  # Clean up space after `omp` in case the first clause was removed.
  s/(\bomp)[[:space:]]+/\1 /
  # Trim any trailing whitespace.
  s/[[:space:]]+$//
}
' "$file"