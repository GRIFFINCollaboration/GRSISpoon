#!/bin/bash
# source me!!!

# this should be sourced, not executed, to work properly
if [[ "$_" == $0 ]]; then
    echo "Try sourcing me!";
    exit 0;
fi

SOURCEDFILE=`readlink -f $BASH_SOURCE`

export GRSISYS=`dirname $SOURCEDFILE`
echo "GRSISYS is now $GRSISYS"

MIDASSYS=${MIDASSYS:-/opt/midas}
ROOTSYS=${ROOTSYS:-/opt/root}

if [ ! -d $MIDASSYS ]; then
    echo "MIDASSYS=$MIDASSYS does not point to a directory. Please rectify."
    return 0;
fi
if [ ! -d $ROOTSYS ]; then
    echo "ROOTSYS=$ROOTSYS does not point to a directory. Please rectify."
    return 0;
fi

export MIDASSYS
echo MIDASSYS is now $MIDASSYS

export LD_LIBRARY_PATH=$PWD/libraries:$MIDASSYS/linux/lib

cd $ROOTSYS
source bin/thisroot.sh
cd - > /dev/null

export ROOTENV_NO_HOME=1
echo ROOTSYS is now $ROOTSYS
echo LD_LIBRARY_PATH is now $LD_LIBRARY_PATH

# clean up variables
unset SOURCEDFILE


