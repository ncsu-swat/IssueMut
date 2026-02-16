#!/bin/bash

if [ "$#" -ne 1 ];
then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# This script replaces Intel intrinsic function calls that have arguments
# with their corresponding 'setzero' equivalent, which takes no arguments.
#
# The script is designed to be robust by correctly identifying the function
# prefix (_mm, _mm256, _mm512), the operation, and the type suffix.
#
# Key features of the regex:
# - `(_mm(512|256)?)`: Captures the intrinsic prefix.
# - `_[a-zA-Z0-9]+`: Matches the operation part of the function name. This is
#   a crucial part of the fix. The original script used a more generic
#   `_[a-zA-Z][a-zA-Z0-9_]*` which incorrectly matched complex function names
#   containing underscores (like `_maskz_loadu`). By restricting the operation
#   name to not contain underscores, we avoid replacing complex intrinsics
#   like masked loads/stores.
# - `(_epi...|_si...|_(ps|pd))`: Matches and captures the type suffix.
# - `\s*\([^)]+\)`: Matches a non-empty argument list, ignoring whitespace.
#   This is crucial to avoid replacing existing `setzero` calls which have
#   empty argument lists.
#
# The substitution rules are ordered from most specific (512-bit) to least
# specific to prevent incorrect partial matches.

sed -i -E '
# Integer Intrinsics (e.g., _epi32, _si256)
# Replace with _setzero_si<width>(). Order is 512 -> 256 -> 128 bit.
s/(_mm512)_[a-zA-Z0-9]+(_epi(u)?[0-9]+|_si512)\s*\([^)]+\)/\1_setzero_si512()/g
s/(_mm256)_[a-zA-Z0-9]+(_epi(u)?[0-9]+|_si256)\s*\([^)]+\)/\1_setzero_si256()/g
s/(_mm)_[a-zA-Z0-9]+(_epi(u)?[0-9]+|_si128)\s*\([^)]+\)/\1_setzero_si128()/g

# Floating-Point Intrinsics (ps, pd)
# Replace with _setzero_ps() or _setzero_pd().
# This single rule handles _mm, _mm256, and _mm512 prefixes.
s/(_mm(256|512)?)_[a-zA-Z0-9]+_(ps|pd)\s*\([^)]+\)/\1_setzero_\3()/g
' "$file"