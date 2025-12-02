#!/bin/env bash

set -e
cd cpp-ws
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
    -DCMAKE_PREFIX_PATH=build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1

mkdir -p .log
TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")
cmake --build build -j$(nproc) 2>&1 | tee .log/conan_build_$TIMESTAMP.log
echo "Done"