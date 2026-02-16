#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# Step 1: Find all thread-local variable names. This version is more robust
# for various declaration styles, with or without initializers.
tls_vars_list=$(grep '_Thread_local' "$file" | \
                sed -E 's/=[^;]*//; s/.*[[:space:]*]+([[:alnum:]_]+)[[:space:]]*;?/\1/' | \
                grep -E -v '^\s*$' | \
                sort -u)

if [ -z "$tls_vars_list" ]; then
    exit 0
fi

# Step 2: Create a regex alternation of all thread-local variable names.
tls_vars_regex="($(echo "$tls_vars_list" | paste -sd'|' -))"

# Step 3: Find lines that declare a local variable as a copy of a thread-local one.
# The regex for the type is made more general and correctly handles the space
# between the type and the variable name.
assignment_pairs=$(sed -nE "s/^[[:space:]]*[a-zA-Z0-9_][a-zA-Z0-9_ \t*]*[[:space:]]+\b([a-zA-Z0-9_]+)\b[[:space:]]*=[[:space:]]*\b${tls_vars_regex}\b[[:space:]]*;/\\1 \\2/p" "$file")

if [ -z "$assignment_pairs" ]; then
    exit 0
fi

# Step 4: Build a single sed script to perform all replacements and deletions.
sed_script=""
while read -r local_var global_var; do
    # Skip empty or invalid pairs that might be read.
    if [ -z "$local_var" ] || [ -z "$global_var" ] || [ "$local_var" = "$global_var" ]; then
        continue
    fi

    # Create a precise pattern to match the declaration line for deletion.
    # This pattern must be consistent with the one used to find the pairs.
    decl_pattern="^[[:space:]]*[a-zA-Z0-9_][a-zA-Z0-9_ \t*]*[[:space:]]+\b${local_var}\b[[:space:]]*=[[:space:]]*\b${global_var}\b[[:space:]]*;"

    # Command to substitute `local_var` with `global_var` on all lines EXCEPT the declaration.
    # This prevents changing the declaration line itself, which would prevent its deletion.
    subst_cmd="/${decl_pattern}/!s/\\b${local_var}\\b/${global_var}/g"

    # Command to delete the declaration line.
    delete_cmd="/${decl_pattern}/d"

    sed_script+="${subst_cmd};${delete_cmd};"

done < <(echo "$assignment_pairs" | sort -u)

# Step 5: Apply the generated sed script to the file if it's not empty.
if [ -n "$sed_script" ]; then
    sed -i -E "$sed_script" "$file"
fi