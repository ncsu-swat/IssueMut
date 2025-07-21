#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
s/(VALIDATE\([^,]+,[[:space:]]*)16([,[:space:]]*)31(\))/\115\233\3/
/unsigned long long res = a \/ b;/ {
  N
  s/(if \(res != )15(ULL\))/\116\2/
}
s/(check\([^,]+,[[:space:]]*)64(ULL\))/\163\2/
/int divisor = 8;/,/if \(result != 12\)/ {
  s/(divisor = )8/\17/
  s/(result != )12/\114/
}
/foo\(/,/if \(x != / {
  s/0x8000000000000000000000000000000uwb/0x7ffffffffffffffffffffffffffffffuwb/
  s/0x1ffffffffffffffff8uwb/0x1fffffffffffffffffuwb/
}
' "$file"