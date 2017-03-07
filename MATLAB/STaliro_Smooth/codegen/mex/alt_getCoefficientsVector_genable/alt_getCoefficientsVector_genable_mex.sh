MATLAB="/usr/local/MATLAB/R2015b"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/mlab-retro/.matlab/R2015b"
OPTSFILE_NAME="./setEnv.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for alt_getCoefficientsVector_genable" > alt_getCoefficientsVector_genable_mex.mki
echo "CC=$CC" >> alt_getCoefficientsVector_genable_mex.mki
echo "CFLAGS=$CFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CLIBS=$CLIBS" >> alt_getCoefficientsVector_genable_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CXX=$CXX" >> alt_getCoefficientsVector_genable_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CXXLIBS=$CXXLIBS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "LD=$LD" >> alt_getCoefficientsVector_genable_mex.mki
echo "LDFLAGS=$LDFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> alt_getCoefficientsVector_genable_mex.mki
echo "Arch=$Arch" >> alt_getCoefficientsVector_genable_mex.mki
echo OMPFLAGS=-fopenmp -DOMPLIBNAME='"\"/usr/local/MATLAB/R2015b/sys/os/glnxa64/libiomp5.so\""' >> alt_getCoefficientsVector_genable_mex.mki
echo OMPLINKFLAGS=-fPIC -L/usr/local/MATLAB/R2015b/sys/os/glnxa64 -liomp5 >> alt_getCoefficientsVector_genable_mex.mki
echo "EMC_COMPILER=gcc" >> alt_getCoefficientsVector_genable_mex.mki
echo "EMC_CONFIG=optim" >> alt_getCoefficientsVector_genable_mex.mki
"/usr/local/MATLAB/R2015b/bin/glnxa64/gmake" -B -f alt_getCoefficientsVector_genable_mex.mk
