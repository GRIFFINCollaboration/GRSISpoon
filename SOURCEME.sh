# source me!!!

export GRSISYS=$PWD
echo GRSISYS is now $GRSISYS
export MIDASSYS=/opt/midas
echo MIDASSYS is now $MIDASSYS
export LD_LIBRARY_PATH=$PWD/libraries:$MIDASSYS/linux/lib
echo LD_LIBRARY_PATH is now $LD_LIBRARY_PATH
# export ROOTENV_NO_HOME=1
CURRENT=${PWD}
cd /opt/root/bin
source thisroot.sh
echo ROOTSYS is now $ROOTSYS
cd ${CURRENT}

