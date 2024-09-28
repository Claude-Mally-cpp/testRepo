#!/bin/bash
# Bash script to run clang-tidy on the entire project with optional change argument

SRC_DIR="source"
BUILD_DIR="build"
CONFIG_FILE=".clang-tidy"
CLANG_TIDY="clang-tidy"
CLANG_TIDY_OPTIONS=""

# Check for -change argument
if [[ "$1" == "-change" ]]; then
  CLANG_TIDY_OPTIONS="-fix -fix-errors"
  echo "Running clang-tidy with automatic changes enabled."
fi

# Ensure build directory exists
if [ ! -d "$BUILD_DIR" ]; then
  echo "Build directory does not exist. Please build the project first."
  exit 1
fi

# Run clang-tidy on all .cpp files in the source directory
find "$SRC_DIR" -name "*.cpp" | while read -r file; do
  echo "Running clang-tidy on $file"
  "$CLANG_TIDY" -p "$BUILD_DIR" "$file" --config-file="$CONFIG_FILE" $CLANG_TIDY_OPTIONS
done

echo "Clang-tidy analysis complete."
