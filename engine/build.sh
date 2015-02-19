#!/bin/bash

UNAME=`uname`
# get hostname
if [ "$UNAME" = "SunOS" ]; then
    HOSTNAME=`hostname`
elif [ "$UNAME" = "Darwin" ]; then
    HOSTNAME=`hostname -s`
else
    HOSTNAME="UNKOWN"
fi

ENGINEDIR=`pwd`
PROJECTROOTDIR=`dirname $ENGINEDIR`
APPDIR="$PROJECTROOTDIR/app/"
BOOSTDIR="$PROJECTROOTDIR/include/boost_1_57_0"
SYMLINKS=( "$ENGINEDIR/include/boost" "$APPDIR/include/boost" )

# if unix.cse.tamu.edu check for boost
if [ "$UNAME" = "SunOS" ]; then
    echo "Checking if you have Boost 1.57.0"
    if [ -d "$BOOSTDIR" ]; then
        echo "You have boost 1.57.0. Checking symlinks..." 
        for i in "${SYMLINKS[@]}"
        do
            if [ ! -h "$i" ]; then
                echo "Symlink $i doesn't exist..."
                echo "Creating $i -> $BOOSTDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s $PROJECTROOTDIR/include/boost_1_57_0/ boost
            fi
        done
        cd $ENGINEDIR
        echo "Done!"
        # if you don't have boost
    else
        echo "You don't have boost 1.57.0"
        cd $/include/
        echo "Downloading Boost 1.57.0..."
        wget https://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.bz2
        echo "Extracting in include...(this takes awhile)..."
        tar -xvjf boost_1_57_0.tar.bz2
        echo "Told you it took a long time!"
        echo "Creating Symlinks..."
        for i in "${SYMLINKS[@]}"
        do
            if [ ! -h "$i" ]; then
                echo "Symlink $i -> $BOOSTDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s $PROJECTROOTDIR/include/boost_1_57_0/ boost
            fi
        done
        cd $ENGINEDIR
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
    if [ "$HOSTNAME" = "Tron" ]; then
        #ccache
        CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]; then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        #clang
        #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        #g++
        CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]; then 
            echo "Release Tests Build Failed"
            exit 1
        fi
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
    if [ "$HOSTNAME" = "Tron" ]; then
        #ccache
        CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]; then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        #clang
        #CC="/usr/local/opt/llvm/bin/clang" CXX="/usr/local/opt/llvm/bin/clang++" cmake ..
        #g++
        CC="/usr/local/bin/gcc-4.9 -fdiagnostics-color=auto" CXX="/usr/local/bin/g++-4.9 -fdiagnostics-color=auto" cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]; then 
            echo "Debug Tests Build Failed"
            exit 1
        fi
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

