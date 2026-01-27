#!/usr/bin/env python3
"""
LaTeX log file reformatter.

This script reformats LaTeX log files by:
1. Unwrapping lines that were split at 79 characters
2. Applying indentation based on parenthesis nesting (file inclusion depth)
"""

import sys

WRAP_LENGTH = 79


def split_on_parens(buffer):
    """Split buffer so '(' starts new lines and ')' ends lines."""
    segments = []
    current = ""

    for char in buffer:
        if char == '(':
            if current:  # Output what came before
                segments.append(current)
                current = ""
            current = char  # Start new segment with (
        elif char == ')':
            current += char  # Include )
            segments.append(current)  # End segment after )
            current = ""
        else:
            current += char

    if current:
        segments.append(current)

    return segments


def main():
    # Determine input file
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = "gliederung.log"

    indent = 0
    buffer = ""

    for line in open(filename, encoding='latin-1'):
        # Strip newline from line
        line = line.rstrip('\n')
        buffer += line

        if len(line) < WRAP_LENGTH:
            # Line is complete, split and output segments
            segments = split_on_parens(buffer)

            for segment in segments:
                print(" " * indent + segment)

                # Update indent for NEXT segment based on parens
                for char in segment:
                    if char == '(':
                        indent += 4
                    elif char == ')':
                        indent = max(0, indent - 4)

            buffer = ""

    # Handle any remaining buffer at EOF
    if buffer:
        segments = split_on_parens(buffer)
        for segment in segments:
            print(" " * indent + segment)
            for char in segment:
                if char == '(':
                    indent += 4
                elif char == ')':
                    indent = max(0, indent - 4)


if __name__ == "__main__":
    main()
