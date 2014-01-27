# source me!!!

export MIDASSYS=/opt/midas
echo MIDASSYS is now $MIDASSYS
export LD_LIBRARY_PATH=$PWD/libraries:$MIDASSYS/linux/lib
echo LD_LIBRARY_PATH is now $LD_LIBRARY_PATH
CURRENT=${PWD}
cd /opt/root/bin
source thisroot.sh
echo ROOTSYS is now $ROOTSYS
cd ${CURRENT}

