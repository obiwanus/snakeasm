#!/bin/bash

mkdir -p build
clang c/main.cc -o snakeasm.out -lSDL2
