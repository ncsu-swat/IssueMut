#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script failed with an "Invalid preceding regular expression" error.
# This error is often caused by using regex features not supported by the target
# `sed` implementation, even when the -E flag for extended regular expressions is used.
# The likely culprit in the original script was the non-capturing group syntax (?:...),
# which is not universally supported.
#
# This corrected script resolves the issue by replacing the non-capturing groups
# with standard capturing groups `(...)`. This requires adjusting the backreference
# numbers (e.g., \1, \2) in the replacement part of the `s` command to account for
# the newly introduced capturing groups. This approach increases portability across
# different `sed` versions, such as those found on GNU/Linux and macOS/BSD.

sed -i -E '
/^#else/,/^#endif/ {
    # Update comments to reflect the syntax change from Intel to AT&T
    s/Intel syntax/AT\&T syntax/g
    s/intel syntax/at\&t syntax/g

    # Handle instructions with an immediate value operand (e.g., "add reg, 10").
    # The regex is split into capturing groups:
    # \1: The full `asm` prefix, e.g., `asm volatile("`
    # \2: The `asm` keyword part, e.g., `asm volatile`
    # \3: The optional `volatile` part (captured but not used in replacement)
    # \4: The mnemonic and space, e.g., `add `
    # \5: The destination operand (register), e.g., `ebx`
    # \6: The source operand (immediate), e.g., `10`
    # \7: The closing part of the string, e.g., `");`
    # The replacement string reassembles these parts in AT&T order with new formatting.
    s/(\b(__asm__|asm(\s+volatile)?)\b\s*\(")(\w+\s+)(\w+)\s*,\s*([0-9]+)(\s*"\);?)/\1\4$\6, %\5\7/g

    # Handle instructions with a register operand (e.g., "sub reg1, reg2").
    # The capturing groups are analogous to the command above, but group \6
    # captures a register name instead of a number.
    s/(\b(__asm__|asm(\s+volatile)?)\b\s*\(")(\w+\s+)(\w+)\s*,\s*([a-zA-Z]\w*)(\s*"\);?)/\1\4%\6, %\5\7/g
}
' "$file"