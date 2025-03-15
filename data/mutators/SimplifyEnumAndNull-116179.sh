#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

FILE="$1"

# Extract all enums and their corresponding values
declare -A ENUM_VALUES

# Parse the file for enums and their values
while IFS= read -r line; do
    # Match enum definitions, extract enum names and values
    if echo "$line" | grep -qP 'enum\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\{.*\};'; then
        ENUM_BODY=$(echo "$line" | grep -oP '\{.*\}' | tr -d '{}')
        
        # Split the enum body into individual items
        IFS=',' read -ra ITEMS <<< "$ENUM_BODY"
        VALUE=0
        for ITEM in "${ITEMS[@]}"; do
            ITEM=$(echo "$ITEM" | xargs) # Trim spaces
            if echo "$ITEM" | grep -q '='; then
                KEY=$(echo "$ITEM" | cut -d'=' -f1 | xargs)
                VALUE=$(echo "$ITEM" | cut -d'=' -f2 | xargs)
            else
                KEY="$ITEM"
            fi
            ENUM_VALUES["$KEY"]="$VALUE"
            VALUE=$((VALUE + 1))
        done
    fi
done < "$FILE"

# Replace enum usages in the code
for KEY in "${!ENUM_VALUES[@]}"; do
    sed -i -E "s/\\b$KEY\\b/${ENUM_VALUES[$KEY]}/g" "$FILE"
done

# Remove the enum definition lines
sed -i -E 's/enum\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\{.*\};/enum \1 {};/' "$FILE"
sed -i -E 's/ = nullptr;/;/' "$FILE"
sed -i -E 's/ = nullptr/ = 0/' "$FILE"