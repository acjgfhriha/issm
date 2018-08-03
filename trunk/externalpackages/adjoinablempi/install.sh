#!/bin/bash
set -eu

#Some cleanup
rm -rf src  install

# Keeping this for potential future use
#Mercurial cloning: 
#hg clone -r 268 http://mercurial.mcs.anl.gov//ad/AdjoinableMPI src

#Download from ISSM server
$ISSM_DIR/scripts/DownloadExternalPackage.py 'http://issm.jpl.nasa.gov/files/externalpackages/adjoinablempi' 'adjoinablempi.tar.gz'

#Untar ADOL-C
tar -zxf  adjoinablempi.tar.gz

#Configure adjoinablempi
cd src
./configure \
	--prefix="$ISSM_DIR/externalpackages/adjoinablempi/install" \
	--libdir="$ISSM_DIR/externalpackages/adjoinablempi/install/lib" \
	--with-mpi-root="$ISSM_DIR/externalpackages/mpich/install" \
	--enable-requestOnTrace

#Compile adjoinablempi 
make clean
if [ $# -eq 0 ]; then
	make 
else
	make -j $1
fi
make install
