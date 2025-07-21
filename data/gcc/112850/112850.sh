#!/bin/bash
sed -i -E '
# Find the start of a while loop with a brace on the same line.
/^[[:space:]]*while[[:space:]]*\(.*\)[[:space:]]*\{/ {
    # This section collects all lines of the while loop block
    # by ensuring braces are balanced.
    :collect_block
    h
    s/\n/\x01/g
    :balance_braces
    s/\{[^{}]*\}/ /
    t balance_braces
    # If an open brace remains, the block is not yet complete.
    /\{/ {
        g
        N
        b collect_block
    }
    # Block is complete, restore it from hold space.
    g

    # Now, transform the collected `while` block into a `do-while` block.
    
    # 1. Store the complete block in hold space.
    h
    
    # 2. Isolate the condition. To do this robustly, we work on a copy
    #    of the first line only, avoiding greedy matches over the whole body.
    #    This assumes the condition and opening brace are on the same line as `while`,
    #    which is enforced by the initial pattern.
    s/\n.*//
    s/^[[:space:]]*while[[:space:]]*\((.*)\)[[:space:]]*\{.*/\1/
    
    # 3. Swap pattern space (condition) and hold space (the block).
    x
    
    # 4. Modify the block in pattern space.
    #    a. Replace `while(...) {` with `do {`, preserving indentation.
    s/^([[:space:]]*)while[^{]*\{/\1do {/
    #    b. Remove the final closing brace and any trailing whitespace from the block.
    s/\}[[:space:]]*$//
    
    # 5. Append the `while(condition);` part.
    #    G appends a newline and the hold space (the condition).
    G
    #    Re-form the end of the loop. The first (.*) is greedy and captures the
    #    entire body. The second (.*) captures the condition.
    s/(.*)\n(.*)$/\1} while (\2);/
}
' "$1"