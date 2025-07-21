#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>" >&2
    exit 1
fi

file="$1"

# Step 1: Find all members that are declared as direct struct/union instances.
# The regex targets lines inside a struct definition that declare a member
# like "struct Type member;" but not "struct Type *member;".
# The names of these members are collected into a sed-compatible alternation
# group (e.g., "start|end|manager"). This is done by finding lines that
# start with optional whitespace, 'struct' or 'union', a type name, a member name,
# and a semicolon. It correctly ignores existing pointer declarations.
MEMBERS=$(sed -n -E 's/^[[:space:]]*(struct|union)[[:space:]]+[a-zA-Z0-9_]+[[:space:]]+([a-zA-Z0-9_]+)[[:space:]]*;.*/\2/p' "$file" | tr '\n' '|' | sed -E 's/\|$//')

# If no such members were found, there is nothing to do.
if [ -z "$MEMBERS" ]; then
    exit 0
fi

# Step 2: Perform the transformations.
# The script uses a single sed command with two expressions to modify the file in-place.
#
# Expression 1: Add a pointer '*' to the member declarations.
# It matches the original declaration line for the members found in Step 1.
# The use of ($MEMBERS) ensures we only modify the declarations of the
# members we've identified. The pattern is anchored to the start of the line
# to avoid unintended matches.
# e.g., `    struct Point start;` -> `    struct Point *start;`
#
# Expression 2: Update member access from dot '.' to arrow '->'.
# It finds occurrences of `member.` where `member` is one of the names from
# our list and replaces the dot with an arrow. The `\b` ensures we match
# on a whole-word boundary, preventing partial matches on longer names.
# This lexical replacement is applied globally, which is the standard limitation
# of `sed` as it lacks semantic context (e.g., it cannot know the type of a
# variable to see which struct's member is being accessed). This corrected script
# refines the logic of the original faulty script by removing the incorrect
# reverse-transformation part and using precise regexes for the intended goal.
# e.g., `l.start.x` -> `l.start->x`
# e.g., `dept->manager.id` -> `dept->manager->id`
sed -i -E \
    -e "s/(^[[:space:]]*(struct|union)[[:space:]]+[a-zA-Z0-9_]+[[:space:]]+)($MEMBERS)([[:space:]]*;.*)/\1*\3\4/" \
    -e "s/\b($MEMBERS)\.([a-zA-Z0-9_]+)/\1->\2/g" \
    "$file"