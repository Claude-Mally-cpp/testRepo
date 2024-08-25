#!/bin/bash
./clang-format-all.sh ./source/ ./include/hobby/ ./standalone/source/ ./test/source/
./checkCmakeFormatting.sh
