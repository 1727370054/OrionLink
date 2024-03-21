#!/bin/bash

script_dir=$(dirname "$(readlink -f "$0")")

build_dir="$script_dir/build"

if [ -d "$build_dir" ]; then
    cd "$build_dir" || { echo "Unable to enter build directory"; exit 1; }

    rm -rf *

    cd ..
else
    echo "Build directory not found"
fi

echo "Cleaned build directory"