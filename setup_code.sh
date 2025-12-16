#!/bin/bash
set -e

# Script to build and install all code in code/

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CODE_DIR="$SCRIPT_DIR/code"
BUILD_DIR="$CODE_DIR/build"

echo "Configuring with CMake..."
cmake -S "$CODE_DIR" -B "$BUILD_DIR"

echo "Building all targets..."
cmake --build "$BUILD_DIR" -j$(nproc)

echo "Installing..."
cmake --install "$BUILD_DIR"

echo "Build and installation completed successfully!"
echo "Binaries installed to: ~/.local/tsa/bin"
echo "Libraries installed to: ~/.local/tsa/lib"
