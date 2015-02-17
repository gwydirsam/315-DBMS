#!/bin/bash
UNAME=`uname`
echo "Removing old build directory"
rm -rf build;
echo "Creating build directory..."
mkdir -p build/release build/debug;

cd build/release;
echo "Running cmake for Release with Tests"
#if OS X
if [ "$UNAME" = "Darwin" ]
then
    #clang
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
    #g++
    CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Release Tests Build Failed"
        exit 1
    fi
# if Solaris
elif [ "$UNAME" = "SunOS" ]
then
    CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Release Tests Build Failed"
        exit 1
    fi
else
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Release Tests Build Failed"
        exit 1
    fi
fi
cd ../debug;
echo "Running cmake for Debug with Tests"
#if OS X
if [ "$UNAME" = "Darwin" ]
then
    #clang
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
    #g++
    CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Debug Tests Build Failed"
        exit 1
    fi
# if Solaris
elif [ "$UNAME" = "SunOS" ]
then
    CC="/opt/csw/bin/gcc -fdiagnostics-color=auto" CXX="/opt/csw/bin/g++ -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Debug Tests Build Failed"
        exit 1
    fi
else
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
    RESULT=$?
    if [ $RESULT -ne 0 ]; then 
        echo "Debug Tests Build Failed"
        exit 1
    fi
fi
exit 0

