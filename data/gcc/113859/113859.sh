#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The script operates as a state machine processing C code line-by-line.
# State is stored in sed's hold space.
# 1. It identifies function boundaries to scope the changes and reset state.
# 2. Inside a function, it looks for a line casting a pointer to `unsigned char *`.
#    This is the trigger for the transformation.
# 3. Upon finding the cast, it uses the function signature (saved in hold space)
#    to determine the original pointer's type (`unsigned short/int` or `unsigned long long`).
# 4. Based on the type, it creates a state string "source_var:popcount_func:proxy_var"
#    (e.g., "data:__builtin_popcount:bytes") and stores it in the hold space.
#    It then deletes the cast line.
# 5. Subsequently, it finds assignment lines that sum `__builtin_popcount` results.
#    These can span multiple lines, so it reads ahead until a statement terminator (;) is found.
# 6. It validates that the state has been set, then uses the information from the
#    state string to rewrite the entire summation as a single intrinsic call on the
#    original variable, correctly mapping the array indices.
# 7. The fix involves making the regular expressions more robust and portable by
#    replacing GNU-specific extensions like `\y` with more common ones like `\b`
#    and explicitly defining word characters with `[a-zA-Z0-9_]` instead of `\w`.

sed -i -E '
# Operate only within function bodies
/^\s*void.*\(.*\)\s*\{/,/^\s*}/ {

    # On function signature, store the line in hold space for type lookup.
    /^\s*void.*\(.*\)\s*\{/ {
        h
        b
    }

    # At the end of a function, clear the hold space to reset state.
    /^\s*}/ {
        x; s/.*//; x
        b
    }

    # Match the byte-pointer cast line to extract variable names.
    /^\s*unsigned char\s*\*\s*([a-zA-Z0-9_]+)\s*=\s*\(unsigned char\s*\*\)\s*([a-zA-Z0-9_]+)\s*;/ {
        G # Append function signature from hold space.
        
        # Determine the type of the source variable from the signature and
        # build a state string `source_var:popcount_func:proxy_var` in hold space.
        # Using \b for word boundaries for broad compatibility.
        
        # Case 1: unsigned long long
        s/^\s*unsigned char\s*\*\s*([a-zA-Z0-9_]+)\s*=\s*\(unsigned char\s*\*\)\s*([a-zA-Z0-9_]+)\s*;\n.*\bunsigned long long\b[^,)]*\b\2\b.*/\2:__builtin_popcountll:\1/
        t update_and_delete
        
        # Case 2: unsigned int or unsigned short
        s/^\s*unsigned char\s*\*\s*([a-zA-Z0-9_]+)\s*=\s*\(unsigned char\s*\*\)\s*([a-zA-Z0-9_]+)\s*;\n.*\bunsigned (int|short)\b[^,)]*\b\2\b.*/\2:__builtin_popcount:\1/
        t update_and_delete
        
        # If no match, it is not the pattern we are looking for. Revert G.
        s/\n.*//
        b

        :update_and_delete
        h # Store the state string in hold space.
        d # Delete the cast line.
    }

    # Match the summation line(s).
    /(__builtin_popcount\()/ {
        # Check if we have a valid state in hold space.
        x; /^([a-zA-Z0-9_]+):(__builtin_popcount[a-z]*):([a-zA-Z0-9_]+)$/!{x; b}; x

        # The summation can span multiple lines. Read all of them until the semicolon.
        :loop
        /;\s*$/! {
            N
            b loop
        }
        
        G # Append the state string from hold space to the pattern space.
        
        # Perform the replacement. The regex handles newlines within the statement.
        # It captures indentation, destination var/index, and uses the state
        # string to construct the new, simplified assignment.
        # \1: indentation, \2: dest var, \3: dest index
        # \4: source var, \5: popcount func (from state)
        s/^(\s*)([a-zA-Z0-9_]+)\s*\[\s*([0-9]+)\s*\]\s*=\s*.*;\s*\n([a-zA-Z0-9_]+):(__builtin_popcount[a-z]*):([a-zA-Z0-9_]+)$/\1\2[\3] = \5(\4[\3]);/
    }
}
' "$file"