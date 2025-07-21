#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

# The original script's approach was to first perform a broad substitution
# and then clean up the incorrect changes. The logic was sound, but the
# cleanup rule for 'long long' was faulty.
# 1. `s/\<long\>/long long/g;` incorrectly changes `long long` to `long long long long`.
# 2. The original cleanup `s/long long long/long long/g;` does not correct this.
# 3. The rule for `long double` was correct: `s/long long double/long double/g`.
#
# The fix is to correct the cleanup rule for `long long` to match the actual
# incorrect string that is generated.

sed -i '
    s/\<long\>/long long/g
    s/long long long long/long long/g
    s/long long double/long double/g
' "$file"