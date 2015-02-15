#!/bin/bash
UNAME=`uname`
echo "Removing old build directory"
rm -rf build;
echo "Creating build directory..."
mkdir build;
cd build;
echo "Running cmake"
#if OS X
if [ "$UNAME" = "Darwin" ]
then
    #clang
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
    #g++
    CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake ..
# if Solaris
elif [ "$UNAME" = "SunOS" ]
then
    CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake ..
else
    cmake ..
fi
echo "Now run make in build/. If successful binaries will be in build/src/"
