#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

awk '
function process_buffered_function() {
    local_var = ""
    source_var = ""
    decl_line_num = -1

    for (i = func_body_start_idx; i <= buf_idx; i++) {
        if (match(buffer[i], /^[[:space:]]*svbool_t[[:space:]]+([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*=[[:space:]]*svmov_z\([[:space:]]*[^,]+[[:space:]]*,[[:space:]]*([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*\)/, m)) {
            local_var = m[1]
            source_var = m[2]
            decl_line_num = i
            break
        }
    }

    if (local_var == "") {
        for (i = 1; i <= buf_idx; i++) {
            print buffer[i]
        }
        return
    }

    sig_str = ""
    for (i = 1; i <= func_body_start_idx; i++) {
        sig_str = sig_str buffer[i] " "
    }
    
    sub(/{.*/, "", sig_str)

    if (!match(sig_str, /.*\((.*)\)/, m)) {
        for (i = 1; i <= buf_idx; i++) print buffer[i]
        return
    }
    
    param_list_str = m[1]
    is_param = 0
    if (param_list_str !~ /^[[:space:]]*(void)?[[:space:]]*$/) {
        n = split(param_list_str, params, ",")
        for (j = 1; j <= n; j++) {
            param = params[j]
            gsub(/^[[:space:]]+|[[:space:]]+$/, "", param)
            if (match(param, /[a-zA-Z_][a-zA-Z0-9_]*$/)) {
                param_name = substr(param, RSTART, RLENGTH)
                if (param_name == source_var) {
                    is_param = 1
                    break
                }
            }
        }
    }

    if (is_param) {
        local_var_regex = "\\<" local_var "\\>"
        for (i = 1; i <= buf_idx; i++) {
            if (i == decl_line_num) continue
            
            line = buffer[i]
            gsub(local_var_regex, source_var, line)
            print line
        }
    } else {
        for (i = 1; i <= buf_idx; i++) {
            print buffer[i]
        }
    }
}

{
    buffer[++buf_idx] = $0

    old_brace_level = brace_level
    brace_level += gsub(/{/, "{")
    brace_level -= gsub(/}/, "}")

    if (old_brace_level == 0 && brace_level > 0 && !in_function) {
        in_function = 1
        func_body_start_idx = buf_idx
    }
    
    if (in_function && brace_level == 0) {
        process_buffered_function()
        in_function = 0
        delete buffer
        buf_idx = 0
    }
}

END {
    if (buf_idx > 0) {
        for (i = 1; i <= buf_idx; i++) {
            print buffer[i]
        }
    }
}
' "$file" > "$file.tmp" && mv "$file.tmp" "$file"