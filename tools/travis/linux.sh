#!/bin/bash


set -ex

if [ "$CXX" == "g++" ]; then
  export CXX="g++-4.8";
fi

# Do static validations

tools/validate/format.sh

# Test the code

BUILD_THREADS=2 CXXFLAGS=-Werror ./build.sh

sudo apt-get install clang-3.7
cd bin
  ../tools/clang_tidy.sh | tee clang_tidy_output.txt
  [ ! -s clang_tidy_output.txt ]
cd ..

