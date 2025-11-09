#!/bin/bash

# Compiles all the C++ source files into a single executable
# using the C++11 standard.

echo "Compiling SocialNet..."
g++ -std=c++11 -o SocialNet main.cpp SocialNet.cpp AVLTree.cpp

echo "Compilation complete. Run ./SocialNet"
