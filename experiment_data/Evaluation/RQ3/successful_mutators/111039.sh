#!/bin/bash

sed -i -E '
  # Read the whole file into pattern space to enable multi-line matching
  :a;
  N;
  $!ba;

  # Create a loop to apply transformations repeatedly until no more changes can be made.
  :b;

  # Case 1: The body is a block starting on the same line as the inner `if`.
  # Example: if (c1)\n  if (c2) {
  # This is handled first and specifically matches the opening brace `{` to avoid
  # the greedy `.*` problem with multi-line blocks.
  s/([ \t]*)if[ \t]*\((.*)\)[ \t]*\n([ \t]*)if[ \t]*\((.*)\)([ \t]*\{)/\1if ((\2) \&\& (\4))\5/;
  t b;

  # Case 2: The body is a single statement on the same line as the inner `if`.
  # Example: if (c1)\n  if (c2) statement;
  # This pattern matches after Case 1 fails, so we know the body isn`t a block
  # starting with `{`. It captures any non-empty statement on the same line.
  s/([ \t]*)if[ \t]*\((.*)\)[ \t]*\n([ \t]*)if[ \t]*\((.*)\)([ \t]+\S.*)/\1if ((\2) \&\& (\4))\5/;
  t b;

  # Case 3: The body is on the line following the inner `if`.
  # Example: if (c1)\n  if (c2)\n    body;
  # This handles cases where the inner `if` statement is on a line by itself.
  # It correctly preserves the indentation of the body on the next line.
  s/([ \t]*)if[ \t]*\((.*)\)[ \t]*\n([ \t]*)if[ \t]*\((.*)\)[ \t]*\n([ \t]*)(\S.*)/\1if ((\2) \&\& (\4))\n\5\6/;
  t b;
' "$1"