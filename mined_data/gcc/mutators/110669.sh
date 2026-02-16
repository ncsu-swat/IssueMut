#!/bin/bash

if [ "$#" -ne 1 ]; then
    exit 1
fi

file="$1"
temp_file=$(mktemp)

awk '
NR==FNR {
    if (!found_decl && /^[[:space:]]*extern.*\[.*\];/) {
        s = $0
        sub(/^[[:space:]]*extern[[:space:]]+/, "", s)
        sub(/;[[:space:]]*$/, "", s)
        sub(/\s*\[.*\]/, "", s)
        
        n = split(s, parts, /[[:space:]]+/)
        decl_var = parts[n]
        
        decl_type = ""
        for (i = 1; i < n; i++) {
            decl_type = decl_type (decl_type == "" ? "" : " ") parts[i]
        }
        
        found_decl = 1
    }
    next
}

/.*\([^\)]*\)[[:space:]]*\{[[:space:]]*\}/ {
    sub(/\{[[:space:]]*\}/, "{\n    extern " decl_type " " decl_var ";\n}")
    print
    next
}

state == 1 {
    if ($0 ~ /^[[:space:]]*\}/) {
        print "    extern " decl_type " " decl_var ";"
        state = 0
    } else if ($0 !~ /^[[:space:]]*$/) {
        state = 0
    }
    print
    next
}

/.*\([^\)]*\)[[:space:]]*\{[[:space:]]*$/ {
    state = 1
    print
    next
}

{ 
    print 
}
' "$file" "$file" > "$temp_file" && mv "$temp_file" "$file"