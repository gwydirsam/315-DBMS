#!/bin/bash
echo "Removing old build directory"
rm -rf build;
echo "Creating build directory..."
mkdir build;
cd build;
echo "Running cmake"
CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake ..
echo "Now run make in build/. If successful binaries will be in build/src/"
