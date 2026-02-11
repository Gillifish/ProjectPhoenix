#!/bin/bash

# Created by Claude Code

set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
EXECUTABLE="$BUILD_DIR/bin/ProjectPhoenix"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found. Run ./build.sh first."
    exit 1
fi

echo "=== Running Project Phoenix ==="
echo ""
"$EXECUTABLE"
