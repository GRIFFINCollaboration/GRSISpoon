#!/bin/tcsh 
# source me!!!

# this should be sourced, not executed, to work properly
set sourced=($_)
if ("$sourced" == "") then
    echo "Try sourcing me!"
    exit 0;
endif

set sourcedfile=`readlink -f $sourced[2]`

setenv GRSISYS `dirname $sourcedfile`
echo "GRSISYS is now $GRSISYS"

if ( ! $?MIDASSYS ) then
    setenv MIDASSYS /opt/midas
endif

if ( ! $?ROOTSYS ) then
    setenv ROOTSYS /opt/root
endif

if ( ! -d $MIDASSYS ) then
    echo "MIDASSYS=$MIDASSYS does not point to a directory. Please rectify."
    exit 0;
endif

if ( ! -d $ROOTSYS ) then
    echo "ROOTSYS=$ROOTSYS does not point to a directory. Please rectify."
    exit 0;
endif

echo MIDASSYS is now $MIDASSYS

setenv LD_LIBRARY_PATH $PWD/libraries:$MIDASSYS/linux/lib

cd $ROOTSYS/bin
source thisroot.csh
cd -

setenv ROOTENV_NO_HOME 1
echo ROOTSYS is now $ROOTSYS
echo LD_LIBRARY_PATH is now $LD_LIBRARY_PATH

#clean up the variables
unset sourced sourcedfile
