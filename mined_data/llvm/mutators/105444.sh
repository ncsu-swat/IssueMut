#!/bin/bash

# Check if a file argument is provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

file="$1"
SEED="$2"

lines_with_new_line=$(grep -n -E 'printf\(".*\\n"\);' "$file")

echo "$lines_with_new_line"

random_lines_with_new_line=$(echo "$lines_with_new_line" | 
                awk -v seed="$SEED" 'BEGIN {
                                       srand(seed); 
                                       count=0;
                                    } 
                                    {
                                      if (count < 2) {
                                        lines[NR] = $0;
                                        count++;
                                      } else {
                                        r = rand();
                                        if (r < 2/NR) {
                                           replace = int(r * 2);
                                           lines[replace + 1] = $0;
                                        }
                                      }
                                    } 
                                    END {
                                      print lines[1];
                                      print lines[2];
                                    }
                                ')

first_new_line_lineo=$(echo "$random_lines_with_new_line" | sed -n "1p" | awk -F ":" '{print $1}')

second_new_line_lineo=$(echo "$random_lines_with_new_line" | sed -n "2p" | awk -F ":" '{print $1}')

sed -i -E "${first_new_line_lineo}s/\\\\n//g" "$file"

sed -i -E "${second_new_line_lineo}s/\\\\n//g" "$file"





