#!/bin/bash

# Specify the files to format (you can add more CMake files if needed)
FILES_TO_FORMAT=(
  "CMakeLists.txt"
  "test/CMakeLists.txt"
  "standalone/CMakeLists.txt"
)

# Flag to track if any files need reformatting
FILES_NEED_FORMATTING=0


# Path to your .cmake-format.yaml configuration file
CONFIG_FILE=".cmake-format.yaml"

# Iterate over the files and check their formatting
for file in "${FILES_TO_FORMAT[@]}"; do
  if [ -f "$file" ]; then
    echo "Checking format of $file..."
    cmake-format --check --config "$CONFIG_FILE" "$file"
    FORMAT_RESULT=$?
    if [ $FORMAT_RESULT -ne 0 ]; then
      echo "$file needs reformatting."
      FILES_NEED_FORMATTING=1
    fi
  else
    echo "$file does not exist."
  fi
done

if [ $FILES_NEED_FORMATTING -ne 0 ]; then
  echo "Some files need reformatting. Please run the following command to fix them:"
  echo "cmake-format -i ${FILES_TO_FORMAT[@]}"
  exit 1
else
  echo "All files are properly formatted."
  exit 0
fi
