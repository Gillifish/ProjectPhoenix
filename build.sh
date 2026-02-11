#!/bin/bash

# Created by Claude Code

set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
BUILD_TYPE="${1:-Debug}"

echo "=== Project Phoenix Build Script ==="
echo "Build type: $BUILD_TYPE"
echo ""

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Build
echo ""
echo "Building..."
cmake --build . --parallel

echo ""
echo "Build complete!"
