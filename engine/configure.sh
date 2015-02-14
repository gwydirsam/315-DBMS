#!/bin/bash
echo "Removing old build directory"
rm -rf build;
echo "Creating build directory..."
mkdir build;
echo "cd to build directory..."
cd build;
echo "Running cmake"
CC="/opt/csw/bin/gcc" CXX="/opt/csw/bin/g++" cmake ..
echo "Now run make. If successful binaries will be in src/"
