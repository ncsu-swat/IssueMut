#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file_to_process="$1"

sed -i -E '
# Address range: from a function signature with at least two arguments to its closing brace.
/^[a-zA-Z0-9_[:space:]*]+[[:space:]]+[a-zA-Z0-9_]+[[:space:]]*\([^,]+,.+\)[[:space:]]*\{/,/^[[:space:]]*\}/ {

    # For the function signature line...
    /^[a-zA-Z0-9_[:space:]*]+[[:space:]]+[a-zA-Z0-9_]+[[:space:]]*\([^,]+,.+\)[[:space:]]*\{/ {
        h
        # Isolate the second parameter declaration.
        s/^[^(]*\([^,]+,[[:space:]]*//
        s/[,)].*//
        # Isolate the parameter name by removing its type.
        s/.*[[:space:]*][[:space:]]*//
        # Swap the extracted name into the hold space.
        x
        b
    }

    # Within the function body, find the line with the atomic_load_explicit call.
    /atomic_load_explicit/ {
        # Append the parameter name from the hold space.
        G
        # Proceed only if a parameter name was successfully captured.
        /\n.+/ {
            # Replace `load` with `store`, inserting the captured parameter name.
            # This regex preserves original spacing and handles the optional (void) cast.
            # Groups: 1:indent 2:(void) 3:( 4:arg1, 5:arg2 6:) 7:; 8:new_arg
            s|([[:space:]]*)(\(void\))?[[:space:]]*atomic_load_explicit([[:space:]]*\()([^,]+,)([^)]+)([[:space:]]*\))(.*)\n(.*)|\1atomic_store_explicit\3\4 \8,\5\6\7|
        }
    }
}
' "$file_to_process"