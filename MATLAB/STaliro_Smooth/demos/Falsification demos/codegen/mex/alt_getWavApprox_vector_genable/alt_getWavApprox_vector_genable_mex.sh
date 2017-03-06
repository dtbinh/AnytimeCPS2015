MATLAB="/usr/local/MATLAB/R2015b"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/mlab-retro/.matlab/R2015b"
OPTSFILE_NAME="./setEnv.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for alt_getWavApprox_vector_genable" > alt_getWavApprox_vector_genable_mex.mki
echo "CC=$CC" >> alt_getWavApprox_vector_genable_mex.mki
echo "CFLAGS=$CFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CLIBS=$CLIBS" >> alt_getWavApprox_vector_genable_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CXX=$CXX" >> alt_getWavApprox_vector_genable_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CXXLIBS=$CXXLIBS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "LD=$LD" >> alt_getWavApprox_vector_genable_mex.mki
echo "LDFLAGS=$LDFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> alt_getWavApprox_vector_genable_mex.mki
echo "Arch=$Arch" >> alt_getWavApprox_vector_genable_mex.mki
echo OMPFLAGS=-fopenmp -DOMPLIBNAME='"\"/usr/local/MATLAB/R2015b/sys/os/glnxa64/libiomp5.so\""' >> alt_getWavApprox_vector_genable_mex.mki
echo OMPLINKFLAGS=-fPIC -L/usr/local/MATLAB/R2015b/sys/os/glnxa64 -liomp5 >> alt_getWavApprox_vector_genable_mex.mki
echo "EMC_COMPILER=gcc" >> alt_getWavApprox_vector_genable_mex.mki
echo "EMC_CONFIG=optim" >> alt_getWavApprox_vector_genable_mex.mki
"/usr/local/MATLAB/R2015b/bin/glnxa64/gmake" -B -f alt_getWavApprox_vector_genable_mex.mk
