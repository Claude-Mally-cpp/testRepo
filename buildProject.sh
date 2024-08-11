#!/bin/bash
cmake -S standalone -B build/standalone  -DUSE_STATIC_ANALYZER="clang-tidy|cppcheck"
cmake --build build/standalone
