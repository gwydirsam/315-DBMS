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
GTESTURL="https://googletest.googlecode.com/files/gtest-1.7.0.zip"
GTESTDIR="$PROJECTROOTDIR/include/`basename $GTESTURL .zip`"
GTESTSYMLINKS=( "$ENGINEDIR/include/gtest" "$APPDIR/include/gtest" )

READLINEURL="http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz"
READLINETARFILENAME=`basename $READLINEURL`
READLINEDIR="$PROJECTROOTDIR/include/`basename $BOOSTURL .tar.gz`"
READLINESYMLINKS=( "$ENGINEDIR/include/readline" "$APPDIR/include/readline" )

LOGFILE="$ENGINEDIR/.buildshlog"

echo "Checking if you're on unix.cse.tamu.edu..."
# or my computer! tee hee
if ! [[ "$HOSTNAME" = "sun" || "$HOSTNAME" = "Tron" ]]
then
    echo "You're not on unix.cse.tamu.edu. This program should only be built on unix.cse.tamu.edu"
    exit 1
else
    echo "You are! Well done."
fi

echo "Checking if you have gtest"
if [ -d "$GTESTDIR" ]
then
    echo "You have gtest-1.7.0. Checking symlinks..."
    for i in "${GTESTSYMLINKS[@]}"
    do
        if [ ! -h "$i" ]
        then
            echo "Symlink $i doesn't exist..."
            echo "Creating $i -> $GTESTDIR"
            cd `dirname $i`
            echo "Creating symlink..."
            ln -s "$GTESTDIR" gtest
        fi
    done
    echo "Done!"
else
    # if you don't have gtest
    echo "You don't have gtest 1.7.0"

    # download if you don't have it
    if [ ! -d "$DLDIR" ]
    then
        # if dldir doesn't exist create it
        mkdir -p "$DLDIR"
        # download gtest
        echo "Downloading gtest 1.7.0..."
        wget --no-check-certificate -P "$DLDIR" "$GTESTURL" #>> "$LOGFILE" 2>&1
    else
        # dldir does exist
        # check if gtest zip is already there
        if [ -f "$DLDIR/`basename $GTESTURL`" ]
        then
            # it is there!
            echo "Found $DLDIR/`basename $GTESTURL`"
        else
            # it's not... download
            echo "Downloading gest 1.7.0..."
            wget --no-check-certificate -P "$DLDIR" "$GTESTURL" #>> "$LOGFILE" 2>&1
        fi
    fi

    # extract zip
    echo "Extracting in include..."
    cd "$PROJECTROOTDIR/include/"
    unzip "$DLDIR/`basename $GTESTURL`" #>> "$LOGFILE" 2>&1

    # create symlinks
    echo "Creating Symlinks..."
    for i in "${GTESTSYMLINKS[@]}"
    do
        if [ ! -h "$i" ]
        then
            echo "Symlink $i -> $GTESTDIR"
            cd `dirname $i`
            echo "Creating symlink..."
            ln -s "$GTESTDIR" gtest
        fi
    done

    # cleanup
    rm -rf "$DLDIR"

    echo "Done Installing Gtest 1.7.0!"
fi

# if on unix also check if you have boost and ccache
if [ "$HOSTNAME" = "sun" ]
then
    echo "Checking if you have readline"
    if [ -d "$HOME/usr/include/readline" ]
    then
        echo "You have readline Checking symlinks..."
        for i in "${READLINESYMLINKS[@]}"
        do
            if [ ! -h "$i" ]
            then
                echo "Symlink $i doesn't exist..."
                echo "Creating $i -> $READLINEDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s "$READLINEDIR" readline
            fi
        done
        echo "Done!"
    else
        # if you don't have readline
        echo "You don't have readline"

        # download if you don't have it
        if [ ! -d "$DLDIR" ]
        then
            # if dldir doesn't exist create it
            mkdir -p "$DLDIR"
            # download readline
            echo "Downloading readline..."
            wget --no-check-certificate -P "$DLDIR" "$READLINEURL" #>> "$LOGFILE" 2>&1
        else
            # dldir does exist
            # check if readline zip is already there
            if [ -f "$DLDIR/`basename $READLINEURL`" ]
            then
                # it is there!
                echo "Found $DLDIR/`basename $READLINEURL`"
            else
                # it's not... download
                echo "Downloading gest 1.7.0..."
                wget --no-check-certificate -P "$DLDIR" "$READLINEURL" #>> "$LOGFILE" 2>&1
            fi
        fi

        #create build directory if doesn't exist
        if [ ! -d "$HOME/.tmp/build" ]; then mkdir -p "$HOME/.tmp/build"; fi

        # extract tar
        echo "Extracting Readline..."
        cd "$HOME/.tmp/build"
        tar -zxvf "$DLDIR/`basename $READLINEURL`" #>> "$LOGFILE" 2>&1

        # build
        echo "Building Readline..."
        cd "$HOME/.tmp/build/`basename $READLINEURL .tar.gz`"
        CC="/opt/csw/bin/gcc-4.9" CXX="/opt/csw/bin/g++-4.9" \
          ./configure --prefix="$HOME/usr" #>> "$LOGFILE" 2>&1
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "Readline Configure Failed"
            exit 1
        fi

        make #>> "$LOGFILE" 2>&1
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "CCache Build Failed"
            exit 1
        fi

        make install #>> "$LOGFILE" 2>&1
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then
            echo "CCache Build Failed"
            exit 1
        fi

        # create symlinks
        echo "Creating Symlinks..."
        for i in "${READLINESYMLINKS[@]}"
        do
            if [ ! -h "$i" ]
            then
                echo "Symlink $i -> $READLINEDIR"
                cd `dirname $i`
                echo "Creating symlink..."
                ln -s "$READLINEDIR" readline
            fi
        done

        # cleanup
        rm -rf "$DLDIR"

        echo "Done Installing Readline!"
    fi
fi

# if on unix also check if you have boost and ccache
if [ "$HOSTNAME" = "sun" ]
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
        echo "Checking if you have compiled and installed Boost"
        if [ ! -d "$HOME/usr/include/boost" ] #this may need to be changed
        then
            echo "Compiling and Installing Boost to ~/usr/"
            cd $BOOSTDIR
            ./bootstrap.sh --prefix="$HOME/usr"
            CC="/opt/csw/bin/gcc-4.9" CXX="/opt/csw/bin/g++-4.9" ./b2 install
            echo "Adding ~/usr/lib to LD_LIBRARY_PATH"
            echo 'export LD_LIBRARY_PATH=$HOME/usr/lib:$LD_LIBRARY_PATH' >> "$HOME/.bash_profile"
            echo "Done Compiling and Installing Boost 1.57.0!"
        else
            echo "You have boost installed and compiled."
        fi
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
            wget --no-check-certificate -P "$DLDIR" "$BOOSTURL" #>> "$LOGFILE" 2>&1
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
                wget --no-check-certificate -P "$DLDIR" "$BOOSTURL" #>> "$LOGFILE" 2>&1
            fi
        fi

        # extract tar
        echo "Extracting in include...(this takes awhile...like 5-10 minutes)..."
        cd "$PROJECTROOTDIR/include/"
        tar -xvjf "$DLDIR/$BOOSTTARFILENAME" #>> "$LOGFILE" 2>&1
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
        echo "Compiling and Installing Boost to ~/usr/"
        cd $BOOSTDIR
        ./bootstrap.sh --prefix="$HOME/usr"
        CC="/opt/csw/bin/gcc-4.9" CXX="/opt/csw/bin/g++-4.9" ./b2 install
        echo "Done Compiling and Installing Boost 1.57.0!"
    fi
    # check for ccache
    echo "Checking for CCache..."
    if [ -e "$HOME/usr/bin/ccache/ccache" ]
    then
        echo "CCache Installed."
    else
        echo "CCache Not Found. Installing..."
        echo "CCache will improve compile times..."

        # download if you don't have it
        if [ ! -d "$DLDIR" ]
        then
            # if dldir doesn't exist create it
            mkdir -p "$DLDIR"
            # download ccache
            echo "Downloading CCache..."
            wget --no-check-certificate -P "$DLDIR" "$CCACHEURL" #>> "$LOGFILE" 2>&1
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
                wget --no-check-certificate -P "$DLDIR" "$CCACHEURL" #>> "$LOGFILE" 2>&1
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
        tar -xvjf "$DLDIR/`basename $CCACHEURL`" #>> "$LOGFILE" 2>&1

        # build
        echo "Building CCache..."
        cd "$HOME/.tmp/build/`basename $CCACHEURL .tar.bz2`"
        CC="/opt/csw/bin/gcc-4.9" CXX="/opt/csw/bin/g++-4.9" \
          ./configure --prefix="$HOME/usr" #>> "$LOGFILE" 2>&1
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "CCache Configure Failed"
            exit 1
        fi

        make #>> "$LOGFILE" 2>&1
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "CCache Build Failed"
            exit 1
        fi

        echo "CCache Build Done. Installing to ~/usr/bin/ccache/"

        # install manpage
        cp ccache.1 "$HOME/usr/share/man/man1/."
        cp ccache "$HOME/usr/bin/ccache/."

        echo "Setting up CCache settings..."
        cd "$HOME/usr/bin/ccache/"
        ccache -F 0 #>> "$LOGFILE" 2>&1
        ccache -M10 #>> "$LOGFILE" 2>&1
        # setup symlinks
        ln -s ccache gcc
        ln -s ccache g++
        ln -s ccache cc
        ln -s ccache c++
        ln -s ccache sparc-sun-solaris2.10-gcc-4.9
        ln -s ccache sparc-sun-solaris2.10-g++-4.9

        echo "Adding CCache to Path"
        #add ~/usr/bin and ~/usr/bin/ccache to path
        echo 'export PATH=$HOME/usr/bin/ccache:$HOME/usr/bin:$PATH' >> "$HOME/.bash_profile"
        #add ~/usr/share/man to manpath
        echo 'export MANPATH=$HOME/usr/share/man:$MANPATH' >> "$HOME/.bash_profile"
        #add stuff for gcc
        #echo 'export LD_LIBRARY_PATH=/usr/local/gcc4.9.2/lib64:$LD_LIBRARY_PATH' >> "$HOME/.bash_profile"
        # echo 'export CC="$HOME/usr/bin/ccache/gcc -fdiagnostics-color=auto"' >> "$HOME/.bash_profile"
        # echo 'export CXX="$HOME/usr/bin/ccache/g++ -fdiagnostics-color=auto"' >> "$HOME/.bash_profile"


        # cleanup
        #rm -rf "$HOME/.tmp"

        echo "Done Installing CCache!"
        echo "Run \"source .bash_profile\" to use CCache"
    fi
fi

# touch .buildshran after we ran build.sh and installed everything
touch "$ENGINEDIR/.buildshran"

#echo "Removing old build directory"
#rm -rf "$ENGINEDIR/build";

echo "Running cmake for Release with Tests"
if [ "$HOSTNAME" = "Tron" ]
then
    if [ -d "$ENGINEDIR/build/release" ]
    then
        echo "Running Make Clean in build/release"
        cd "$ENGINEDIR/build/release"
        make clean
        make -j4
        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        cd "$ENGINEDIR"
        echo "Creating build/release directory..."
        mkdir -p "build/release";
        cd "$ENGINEDIR/build/release"
        # CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
        #   CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
        #   cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        #   # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4
        CC="/usr/local/opt/ccache/libexec/clang-3.5.1" \
          CXX="/usr/local/opt/ccache/libexec/clang++-3.5.1" \
          cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Release ../.. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    fi
elif [ "$HOSTNAME" = "sun" ]
then
    if [ -d "$ENGINEDIR/build/release" ]
    then
        echo "Running Make Clean in build/release"
        cd "$ENGINEDIR/build/release"
        make clean
        make -j4
    else
        cd "$ENGINEDIR"
        echo "Creating build/release directory..."
        mkdir -p "build/release";
        cd "$ENGINEDIR/build/release"
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
    if [ -d "$ENGINEDIR/build/debug" ]
    then
        echo "Running make clean in build/debug"
        cd "$ENGINEDIR/build/debug"
        make clean
        make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    else
        cd "$ENGINEDIR"
        echo "Creating build/debug directory..."
        mkdir -p "build/debug";
        cd "$ENGINEDIR/build/debug"
        # CC="/usr/local/opt/ccache/libexec/gcc-4.9 -fdiagnostics-color=auto" \
        #   CXX="/usr/local/opt/ccache/libexec/g++-4.9 -fdiagnostics-color=auto" \
        #   cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
        #   # cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4
        CC="/usr/local/opt/ccache/libexec/clang-3.5.1" \
          CXX="/usr/local/opt/ccache/libexec/clang++-3.5.1" \
          cmake -Dtest=ON -DCMAKE_BUILD_TYPE=Debug ../.. && make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Release Tests Build Failed"
            exit 1
        fi
    fi
elif [ "$HOSTNAME" = "sun" ]
then
    if [ -d "$ENGINEDIR/build/debug" ]
    then
        echo "Running make clean in build/debug"
        cd "$ENGINEDIR/build/debug"
        make clean
        make -j4

        RESULT=$?
        if [ $RESULT -ne 0 ]
        then 
            echo "Debug Tests Build Failed"
            exit 1
        fi
    else
        cd "$ENGINEDIR"
        echo "Creating build/debug directory..."
        mkdir -p "build/debug";
        cd "$ENGINEDIR/build/debug"
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

