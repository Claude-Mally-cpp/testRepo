#!/bin/bash

# Find all CMake files and format them
find . -name "CMakeLists.txt" -o -name "*.cmake" | while read -r file; do
    cmake-format -i -c .cmake-format.yaml "$file"
done
