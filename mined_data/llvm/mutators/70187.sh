#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# 1. Find the line number and the value of the first array index access.
#    We use awk to do this in a single pass for correctness and efficiency.
#    An "access" is defined as the use of `[<digits>]` on a line that is not a
#    C-style declaration. We identify declaration lines by checking if they start
#    with common C type or storage-class keywords.
#    The awk script prints the line number (NR) and the captured index, then exits.
#    The `read` command captures these two values into shell variables.
read -r line_num old_num < <(awk '
/\[[0-9]+\]/ && !/^\s*(typedef|const|volatile|struct|union|enum|int|char|void|float|double|long|short|signed|unsigned)\s/ {
    match($0, /\[([0-9]+)\]/, m)
    print NR, m[1]
    exit
}
' "$file")

# 2. If a matching line was found (i.e., line_num is not empty), proceed.
if [ -n "$line_num" ]; then
    # 3. Calculate the new number using bash's arithmetic expansion.
    new_num=$((old_num * 2 + 1))

    # 4. Perform the in-place replacement on the specific line using sed.
    #    The address `${line_num}` restricts the substitution to only that line.
    #    The substitution replaces the first occurrence of `[<old_num>]` on that
    #    line with `[<new_num>]`, ensuring only the target index is modified.
    sed -i "${line_num}s/\[${old_num}\]/\[${new_num}\]/" "$file"
fi