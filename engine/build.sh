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

ENGINEDIR=`pwd`
PROJECTROOTDIR=`dirname $ENGINEDIR`
APPDIR="$PROJECTROOTDIR/app/"

BOOSTURL="https://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.bz2"
BOOSTTARFILENAME=`basename $BOOSTURL`
BOOSTDIR="$PROJECTROOTDIR/include/`basename $BOOSTURL .tar.bz2`"
BOOSTSYMLINKS=( "$ENGINEDIR/include/boost" "$APPDIR/include/boost" )

DLDIR="/tmp/${USER}dl"

CCACHEURL="http://samba.org/ftp/ccache/ccache-3.2.1.tar.bz2"

LOGFILE="$ENGINEDIR/.buildshlog"

# if unix.cse.tamu.edu check for boost and ccache
if [ "$UNAME" = "SunOS" ]
then
    echo "Checking if you have Boost 1.57.0"
    if [ -d "$BOOSTDIR" ]
    then
        echo "You have boost 1.57.0. Checking symlinks..." 
        for i in "${BOOSTSYMLINKS[@]}"
        do
            if [ ! -h "$i" ]
            then
                echo "Symlink $i doesn't exist..."
                echo "Creating $i -> $BOOSTDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s "$BOOSTDIR" boost
            fi
        done
        echo "Done!"
    else
        # if you don't have boost
        echo "You don't have boost 1.57.0"

        # download if you don't have it
        if [ ! -d "$DLDIR" ]
        then
            # if dldir doesn't exist create it
            mkdir -p "$DLDIR"
            # download boost
            echo "Downloading Boost 1.57.0..."
            wget -P "$DLDIR" "$BOOSTURL" > "$LOGFILE" 2>&1
        else
            # dldir does exist
            # check if boost tar is already there
            if [ -f "$DLDIR/`basename $BOOSTURL`" ]
            then
                # it is there!
                echo "Found $DLDIR/`basename $BOOSTURL`"
            else
                # it's not... download
                echo "Downloading Boost 1.57.0..."
                wget -P "$DLDIR" "$BOOSTURL" > "$LOGFILE" 2>&1
            fi
        fi

        # extract tar
        echo "Extracting in include...(this takes awhile)..."
        cd "$PROJECTROOTDIR/include/"
        tar -xvjf "$DLDIR/$BOOSTTARFILENAME" > "$LOGFILE" 2>&1
        echo "Told you it took a long time!"

        # create symlinks
        echo "Creating Symlinks..."
        for i in "${BOOSTSYMLINKS[@]}"
        do
            if [ ! -h "$i" ]
            then
                echo "Symlink $i -> $BOOSTDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s "$BOOSTDIR" boost
            fi
        done
        echo "Done Installing Boost 1.57.0!"
    fi
    # check for ccache
    echo "Checking for CCache..."
    if [ -e "$HOME/usr/bin/ccache/ccache" ]
    then
        echo "CCache Installed."
    else
        echo "CCache Not Found. Installing..."

        # download if you don't have it
        if [ ! -d "$DLDIR" ]
        then
            # if dldir doesn't exist create it
            mkdir -p "$DLDIR"
            # download ccache
            echo "Downloading CCache..."
            wget -P "$DLDIR" "$CCACHEURL" > "$LOGFILE" 2>&1
        else
            # dldir does exist
            # check if boost tar is already there
            if [ -f "$DLDIR/`basename $CCACHEURL`" ]
            then
                # it is there!
                echo "Found $DLDIR/`basename $CCACHEURL`"
            else
                # it's not... download
                echo "Downloading CCache..."
                wget -P "$DLDIR" "$CCACHEURL" > "$LOGFILE" 2>&1
            fi
        fi

        #create build directory if doesn't exist
        if [ ! -d "$HOME/.tmp/build" ]; then mkdir -p "$HOME/.tmp/build"; fi
        # create ~/usr/bin/ccache/
        if [ ! -d "$HOME/usr/bin/ccache" ]; then mkdir -p "$HOME/usr/bin/ccache"; fi
        #create ~/usr/share/man if doesn't exist
        if [ ! -d "$HOME/usr/share/man/man1" ]; then mkdir -p "$HOME/usr/share/man/man1"; fi

        # extract tar
        echo "Extracting CCache Tar..."
        cd "$HOME/.tmp/build"
        tar -xvjf "$DLDIR/`basename $CCACHEURL`" > "$LOGFILE" 2>&1

        # build
        echo "Building CCache..."
        cd "$HOME/.tmp/build/`basename $CCACHEURL .tar.bz2`"
        ./configure --prefix="$HOME/usr" > "$LOGFILE" 2>&1
        make > "$LOGFILE" 2>&1
        echo "CCache Build Done. Installing to ~/usr/bin/ccache/"
        # install manpage
        cp ccache.1 "$HOME/usr/bin/share/man/man1/."
        cp ccache "$HOME/usr/bin/ccache/."

        # setup symlinks
        cd "$HOME/usr/bin/ccache/"
        ln -s ccache gcc
        ln -s ccache g++
        ln -s ccache cc
        ln -s ccache c++
        ln -s ccache sparc-sun-solaris2.10-gcc-4.9
        ln -s ccache sparc-sun-solaris2.10-g++-4.9

        echo "Adding CCache to Path"
        #add ~/usr/bin and ~/usr/bin/ccache to path
        echo "export PATH=$HOME/usr/bin/ccache:$HOME/usr/bin:$PATH" >> "$HOME/.bash_profile"
        #add ~/usr/share/man to manpath
        echo "export MANPATH=$HOME/usr/share/man:$MANPATH" >> "$HOME/.bash_profile"
        #add stuff for gcc
        echo "export LD_LIBRARY_PATH=/usr/local/gcc4.9.2/lib64:$LD_LIBRARY_PATH" >> "$HOME/.bash_profile"
        echo "export CC=\"$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto\"" >> "$HOME/.bash_profile" 
        echo "export CXX=\"$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto\"" >> "$HOME/.bash_profile" 
        echo "Done Installing CCache!"
        echo "Run \"source .bash_profile\" to use CCache"
    fi
fi

echo "Removing old build directory"
rm -rf "$ENGINEDIR/build";

echo "Creating build directory..."
mkdir -p "$ENGINEDIR/build/release" "$ENGINEDIR/build/debug";

cd "$PROJECTROOTDIR/engine/build/release";
echo "Running cmake for Release with Tests"
if [ "$UNAME" = "Darwin" ]
then
    #if OS X
    CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
    CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Release Tests Build Failed"
        exit 1
    fi
elif [ "$UNAME" = "SunOS" ]
then
    # if Solaris
    CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto" \
    CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto" \
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Release Tests Build Failed"
        exit 1
    fi
fi

cd "$PROJECTROOTDIR/engine/build/debug";
echo "Running cmake for Debug with Tests"
if [ "$UNAME" = "Darwin" ]
then
    #if OS X
    CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
    CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Release Tests Build Failed"
        exit 1
    fi
elif [ "$UNAME" = "SunOS" ]
then
    # if Solaris
    CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto" \
    CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto" \
    cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4

    RESULT=$?
    if [ $RESULT -ne 0 ]
    then 
        echo "Debug Tests Build Failed"
        exit 1
    fi
fi
exit 0

