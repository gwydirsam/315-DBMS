#!/bin/bash
echo "Creating build directory..."
mkdir build;
echo "cd to build directory..."
cd build;
echo "Running cmake\n\n"
CC="/opt/csw/bin/gcc" CXX="/opt/csw/bin/g++" cmake ..
echo "\nNow run make. If successful binaries will be in src/\n"
