#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

vars=$(grep -oP 'nullptr_t\s*\*?\s*\K\b[a-zA-Z_][a-zA-Z0-9_]*\b' "$file" | sort -u | tr '\n' '|')

null_ids_regex="nullptr"
if [[ -n "$vars" ]]; then
    null_ids_regex="nullptr|${vars%|}"
fi

if grep -q -F '[[gnu::sentinel]]' "$file"; then
    # If the sentinel attribute is present, the goal is to remove the (void*) cast
    # as it can interfere with the compiler's sentinel checks.
    sed -i -E "s/\(void \*\)\s*(\b($null_ids_regex)\b)/\1/g" "$file"
else
    # Otherwise, add a (void*) cast to ensure nullptr is treated as a pointer.
    # The regex looks for contexts where a nullptr expression is likely to appear
    # (after '(', ',', '=', '?', ':', or 'return') to avoid incorrectly
    # modifying declarations.
    sed -i -E "s/([,(=\?:]\s*|return\s+)(\b($null_ids_regex)\b)/\1(void*)\2/g" "$file"
fi