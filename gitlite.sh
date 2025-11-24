#!/bin/bash

# GitLite Advanced CLI with OS-level features

EXECUTABLE="./build/gitlite"

if [ ! -f "$EXECUTABLE" ]; then
    echo "❌ Executable not found. Run: make"
    exit 1
fi

# Pass all arguments directly to the C++ executable
$EXECUTABLE "$@"
