#!/bin/bash
UNAME=`uname`
echo "Checking if you have Boost 1.57.0"
if [ "$UNAME" = "SunOS" ]; then
    # if you don't have boost
    if [ -d "../include/boost_1_57_0" ]; then
        echo "You have boost 1.57.0. Continuing..." 
    else
        echo "You don't have boost 1.57.0"
        cd ../include/
        echo "Downloading Boost 1.57.0..."
        wget https://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.bz2
        echo "Extracting in include...(this takes awhile)..."
        tar -xvjf boost_1_57_0.tar.bz2
        echo "Told you it took a long time!"
        echo "Symlinking to engine/include/boot -> ../../boost_1_57_0/ ..."
        cd ../engine/include/
        ln -s ../../boost_1_57_0/ boost
        echo "Symlinking to app/include/boot -> ../../boost_1_57_0/ ..."
        cd ../../app/include/
        ln -s ../../boost_1_57_0/ boost
        cd ../../engine/
        if [ -a "../include/boost_1_57_0.tar.bz2" ]; then
        echo "Deleting inlcude/boost_1_57_0.tar.bz2"
        rm ../include/boost_1_57_0.tar.bz2
        fi
        echo "Done!"
    fi
fi

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
    #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
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

