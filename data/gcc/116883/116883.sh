#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script uses a multi-pass placeholder strategy to robustly replace
# `unsigned int` and its shorthand `unsigned` with `unsigned long`.

# 1. Protection Phase: All `unsigned` types that are NOT the target (`unsigned int`)
#    are replaced with unique placeholders. This prevents them from being affected
#    by the transformation rules. The order of these rules is important,
#    from most-specific to least-specific, to avoid partial matches.
#
# 2. Transformation Phase: The target types (`unsigned int` and `unsigned`) are
#    replaced with a dedicated placeholder for the new type.
#
# 3. Restoration Phase: All placeholders are replaced with their final string
#    representations. The protected types are restored to their original form,
#    and the target placeholder is replaced with `unsigned long`.

sed -i -E '
# Protection Phase
s/\bunsigned\s+long\s+long\s+int\b/__SED_ULLI__/g;
s/\bunsigned\s+long\s+long\b/__SED_ULL__/g;
s/\blong\s+long\s+unsigned\s+int\b/__SED_LLUI__/g;
s/\blong\s+long\s+unsigned\b/__SED_LLU__/g;
s/\bunsigned\s+long\s+int\b/__SED_ULI__/g;
s/\bunsigned\s+long\b/__SED_UL__/g;
s/\blong\s+unsigned\s+int\b/__SED_LUI__/g;
s/\blong\s+unsigned\b/__SED_LU__/g;
s/\bunsigned\s+short\s+int\b/__SED_USI__/g;
s/\bunsigned\s+short\b/__SED_US__/g;
s/\bshort\s+unsigned\s+int\b/__SED_SUI__/g;
s/\bshort\s+unsigned\b/__SED_SU__/g;
s/\bunsigned\s+char\b/__SED_UC__/g;

# Transformation Phase
s/\bunsigned\s+int\b/__SED_TARGET__/g;
s/\bunsigned\b/__SED_TARGET__/g;

# Restoration Phase
s/__SED_ULLI__/unsigned long long int/g;
s/__SED_ULL__/unsigned long long/g;
s/__SED_LLUI__/long long unsigned int/g;
s/__SED_LLU__/long long unsigned/g;
s/__SED_ULI__/unsigned long int/g;
s/__SED_UL__/unsigned long/g;
s/__SED_LUI__/long unsigned int/g;
s/__SED_LU__/long unsigned/g;
s/__SED_USI__/unsigned short int/g;
s/__SED_US__/unsigned short/g;
s/__SED_SUI__/short unsigned int/g;
s/__SED_SU__/short unsigned/g;
s/__SED_UC__/unsigned char/g;
s/__SED_TARGET__/unsigned long/g;
' "$file"