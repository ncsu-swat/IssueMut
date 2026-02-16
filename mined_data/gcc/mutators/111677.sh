#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file="$1"

sed -i -E '
  # Idempotency: if a pragma is already there on its own line, delete it.
  /^\s*#pragma omp declare simd\s*$/d

  # Use "paragraph mode": accumulate consecutive non-empty lines in hold space.
  /./{
    H
    $!d
  }

  # An empty line or EOF triggers processing of the accumulated paragraph.
  x

  # If the paragraph is empty (e.g., consecutive blank lines), just print the newline.
  /./!{
    x
    b
  }

  # Remove the leading newline that H adds.
  s/^\n//

  # If the paragraph does not contain a `) {` sequence (the marker for a
  # function body), then it cannot be a function definition. Branch to the end.
  /\)\s*\{/!b end_logic

  # If the paragraph already starts with the pragma, we are done. (Idempotency)
  /^\s*#pragma omp declare simd/b end_logic

  # The paragraph contains a function, but might also contain other things
  # before it (e.g., typedefs, comments) if there was no separating blank line.
  # We loop, stripping off any initial lines that are not the function signature.
  :find_func_line
    # If the current first line of the paragraph is a comment, control statement,
    # typedef, or preprocessor directive, it is not the function signature.
    # Print it, delete it from the paragraph, and loop to check the next line.
    /^\s*(\/\/|\/\*|if|for|while|switch|typedef|#)/{
      P
      D
    }
    # Also skip over any blank lines within the paragraph.
    /^\s*$/{
      P
      D
    }

  # After the loop, the paragraph starts with the function signature.
  # Insert the pragma at the beginning.
  s/^/#pragma omp declare simd\n/

:end_logic
  # If we are not at the end of the file, append a newline to restore the
  # paragraph separator that was consumed.
  $!a\

' "$file"