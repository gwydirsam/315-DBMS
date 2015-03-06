#!/bin/bash

UNAME=`uname`
# get hostname
if [ "$UNAME" = "Darwin" ]
then
    HOSTNAME=`hostname -s`
else
    HOSTNAME=`hostname`
fi

# get username
USER=`whoami`

# ENGINEDIR=`pwd`
# PROJECTROOTDIR=`dirname $ENGINEDIR`
APPDIR=`pwd`
LIBDIR="$APPDIR/lib"

DLDIR="/tmp/${USER}dl"

echo "Running cmake for Group16 DBMS Library"
if [ "$HOSTNAME" = "Tron" ]
then
    if [ -d "$APPDIR/lib/group16dbms" ]
    then
        echo "Running Make Clean in lib/group16dbms"
        cd "$APPDIR/lib/group16dbms"
        make clean
        make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "Group16 DBMS Library Build Failed"
            exit 1
        fi
    else
        cd "$APPDIR"
        echo "Creating lib/group16dbms directory..."
        mkdir -p "lib/group16dbms";
        cd "$APPDIR/lib/group16dbms"
        CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
          CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
          cmake ../../include/Group16DBMS/. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "Group16 DBMS Library Build Failed"
            exit 1
        fi
    fi
elif [ "$HOSTNAME" = "sun" ]
then
    if [ -d "$APPDIR/lib/group16dbms" ]
    then
        echo "Running Make Clean in lib/group16dbms"
        cd "$APPDIR/lib/group16dbms"
        make clean
        make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "Group16 DBMS Library Build Failed"
            exit 1
        fi
    else
        cd "$APPDIR"
        echo "Creating lib/group16dbms directory..."
        mkdir -p "lib/group16dbms";
        cd "$APPDIR/lib/group16dbms"
        CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto" \
          CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto" \
          cmake ../../include/Group16DBMS/. && make -j4
          # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
    fi

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Group16 DBMS Library Build Failed"
        exit 1
    fi
fi


# #echo "Removing old build directory"
# #rm -rf "$ENGINEDIR/build";

echo "Running cmake for Release with Tests"
if [ "$HOSTNAME" = "Tron" ]
then
    if [ -d "$APPDIR/build/release" ]
    then
        echo "Running Make Clean in build/release"
        cd "$APPDIR/build/release"
        make clean
        make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        cd "$APPDIR"
        echo "Creating build/release directory..."
        mkdir -p "build/release";
        cd "$APPDIR/build/release"
        CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
          CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
          cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
          # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        # CC="/usr/local/opt/ccache/libexec/clang-3.5.1" \
        #   CXX="/usr/local/opt/ccache/libexec/clang++-3.5.1" \
        #   cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    fi
elif [ "$HOSTNAME" = "sun" ]
then
    if [ -d "$APPDIR/build/release" ]
    then
        echo "Running Make Clean in build/release"
        cd "$APPDIR/build/release"
        make clean
        make -j4
    else
        cd "$APPDIR"
        echo "Creating build/release directory..."
        mkdir -p "build/release";
        cd "$APPDIR/build/release"
        CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto" \
          CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto" \
          cmake -Dtest=OFF -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
          # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
    fi

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Release Tests Build Failed"
        exit 1
    fi
fi

echo "Running cmake for Debug with Tests"
if [ "$HOSTNAME" = "Tron" ]
then
    if [ -d "$APPDIR/build/debug" ]
    then
        echo "Running make clean in build/debug"
        cd "$APPDIR/build/debug"
        make clean
        make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        cd "$APPDIR"
        echo "Creating build/debug directory..."
        mkdir -p "build/debug";
        cd "$APPDIR/build/debug"
        CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
          CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
          cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
          # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
        # CC="/usr/local/opt/ccache/libexec/clang-3.5.1" \
        #   CXX="/usr/local/opt/ccache/libexec/clang++-3.5.1" \
        #   cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    fi
elif [ "$HOSTNAME" = "sun" ]
then
    if [ -d "$APPDIR/build/debug" ]
    then
        echo "Running make clean in build/debug"
        cd "$APPDIR/build/debug"
        make clean
        make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Debug Tests Build Failed"
            exit 1
        fi
    else
        cd "$APPDIR"
        echo "Creating build/debug directory..."
        mkdir -p "build/debug";
        cd "$APPDIR/build/debug"
        CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto" \
          CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto" \
          cmake -Dtest=OFF -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
          # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Debug Tests Build Failed"
            exit 1
        fi
    fi
fi
exit 0

