#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E \
-e '/#else/,/#endif/s|// Correctly assumes reversal happens on BE too|// Incorrectly assumes no reversal on BE|' \
-e '/#else/,/#endif/s|(expected = \(my_vec\))\{4, 3, 2, 1\};|\1{1, 2, 3, 4};|' \
-e '/temp\.i = ([0-9]+);/ { N; s|(temp\.i = ([0-9]+);)\n(\s*my_vec = )temp\.v;|\1\n\3(v_i128){\2};|; }' \
-e 's|(printf\("E: )0x%lx%lx\\n", u1\.p\[0\], u1\.p\[1\]\);|\1%lld%llu\\n", (long long)(v_expect[0] >> 64), (unsigned long long)(v_expect[0] \& 0xFFFFFFFFFFFFFFFF));|' \
-e 's|(printf\("A: )0x%lx%lx\\n", u2\.p\[0\], u2\.p\[1\]\);|\1%lld%llu\\n", (long long)(v_actual[0] >> 64), (unsigned long long)(v_actual[0] \& 0xFFFFFFFFFFFFFFFF));|' \
"$file"