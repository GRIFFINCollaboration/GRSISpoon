# source me!!!

setenv MIDASSYS /opt/midas-64
echo MIDASSYS is now $MIDASSYS
setenv LD_LIBRARY_PATH $PWD/libraries:$MIDASSYS/linux/lib
echo LD_LIBRARY_PATH is now $LD_LIBRARY_PATH
set CURRENT=${PWD}
#cd /home/tigress/packages/root_v5.34.07/bin
cd /opt/root/bin
source thisroot.csh
echo ROOTSYS is now $ROOTSYS
cd ${CURRENT}

