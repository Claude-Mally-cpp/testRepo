#!/bin/bash
cmake -S test -B build/test -DUSE_STATIC_ANALYZER="clang-tidy|cppcheck"
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test
