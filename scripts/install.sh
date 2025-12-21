#!/usr/bin/env bash
set -e

TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")

pipx ensurepath
conan profile detect --force
cd cpp-ws
mkdir -p .log
conan install . --output-folder=build --build=missing  2>&1 | tee .log/conan_install_$TIMESTAMP.log