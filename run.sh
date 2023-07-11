#!/bin/sh

# set +xe

clear
clang $1/*.c -o main -lm
./main
rm -rf ./main
