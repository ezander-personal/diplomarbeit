#!/bin/bash
set -e

# Script to prepare data in daten directory

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DATEN_DIR="$SCRIPT_DIR/data"

# Add tsa bin directory to PATH
export PATH="$HOME/.local/tsa/bin:$PATH"

echo "Preparing data in $DATEN_DIR..."
cd "$DATEN_DIR"

# Run prepall script
./prepall

echo "Data preparation completed successfully!"
