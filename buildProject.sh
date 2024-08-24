#!/bin/bash
# rm -rf ./build/
cmake -S standalone -B build/standalone  -DUSE_STATIC_ANALYZER="clang-tidy|cppcheck"
cmake --build build/standalone -- VERBOSE=1
