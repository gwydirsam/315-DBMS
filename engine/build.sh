#!/bin/bash
UNAME=`uname`
echo "Removing old build directory"
rm -rf build;
echo "Creating build directory..."
mkdir -p build/release build/debug;

cd build/release;
echo "Running cmake for Release"
#if OS X
if [ "$UNAME" = "Darwin" ]
then
    #clang
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
    #g++
    CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -DCMAKE_BUILD_TYPE=Release ../.. && make
# if Solaris
elif [ "$UNAME" = "SunOS" ]
then
    CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake -DCMAKE_BUILD_TYPE=Release ../.. && make
else
    cmake -DCMAKE_BUILD_TYPE=Release ../.. && make
fi
cd ../debug;
echo "Running cmake for Release"
#if OS X
if [ "$UNAME" = "Darwin" ]
then
    #clang
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
    #g++
    CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make
# if Solaris
elif [ "$UNAME" = "SunOS" ]
then
    CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make
else
    cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make
fi
cd ..

