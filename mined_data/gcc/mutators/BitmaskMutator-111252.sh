#!/usr/bin/env bash
# Usage: ./toggle_one_ampersand.sh <file>
#
# 1. Finds all occurrences of "& foo" or "& ~foo" in <file>.
# 2. Randomly picks one occurrence.
# 3. Toggles "~" in that single match:
#     - If we see "& ~foo", remove "~"
#     - Else, add "~"

# ------------------------------------------------------------------------------
# 0) Check usage
# ------------------------------------------------------------------------------
if [ $# -ne 2 ]; then
  echo "Usage: $0 <file> <seed>"
  exit 1
fi

file="$1"
SEED=$2

if [ ! -f "$file" ]; then
  echo "Error: '$file' not found."
  exit 1
fi

# ------------------------------------------------------------------------------
# 1) Gather all matches: line_number:matched_text
#    Using grep -n (line #), -o (only match), -E (extended regex)
# ------------------------------------------------------------------------------
matches=$(grep -noE '\&[[:space:]]*~?[[:space:]]*[A-Za-z_][A-Za-z0-9_]*' "$file" | awk -v seed="$SEED" 'BEGIN {srand(seed); line=""} {if (rand() <= 1/NR) line=$0} END {print line}')

# If none found, exit.
if [ -z "$matches" ]; then
  echo "No togglable '&' found in '$file'."
  exit 1
fi

# ------------------------------------------------------------------------------
# 2) Convert matches to array and randomly pick one occurrence
# ------------------------------------------------------------------------------

# The line number is everything before the first colon
line_num="$(cut -d: -f1 <<< "$matches")"
# The matched substring is after the first colon
match_text="$(cut -d: -f2- <<< "$matches")"

echo "Randomly selected line $line_num:"
echo "  Before: $match_text"

# ------------------------------------------------------------------------------
# 3) Toggle "~" in the chosen match
#    IMPORTANT: escape & and ~ in the regex: \& and \~
# ------------------------------------------------------------------------------
if [[ "$match_text" =~ \&[[:space:]]*\~ ]]; then
  # If we have '& ~', remove it
  new_text="$(sed -E 's/\&[[:space:]]*~/\&/' <<< "$match_text")"
else
  # Otherwise, add '~'
  new_text="$(sed -E 's/\&/& ~/' <<< "$match_text")"
fi

echo "  After : $new_text"

# ------------------------------------------------------------------------------
# 4) Replace only that one occurrence on the given line
#    Escape & and / in the old/new substrings for sed
# ------------------------------------------------------------------------------
escaped_old="$(printf '%s' "$match_text" | sed 's/[\/&]/\\&/g')"
escaped_new="$(printf '%s' "$new_text"   | sed 's/[\/&]/\\&/g')"

sed -i "${line_num}s/$escaped_old/$escaped_new/" "$file"

echo "Toggled '~' for one random occurrence in '$file'."