#!/bin/bash
set -eu

rm -rf install

export F77="/usr/local/gfortran/bin/x86_64-apple-darwin10-gfortran"
export CC="/usr/bin/gcc"
export CXX="/usr/bin/g++"
export FFLAGS=-ff2c

#clean up
rm -rf numpy
rm -rf numpy-1.7.0b2

#download numpy first
#export GIT_SSL_NO_VERIFY=true 
#git clone https://github.com/numpy/numpy.git
$ISSM_DIR/scripts/DownloadExternalPackage.py 'http://issm.jpl.nasa.gov/files/externalpackages/numpy-1.7.0b2.tar.gz' 'numpy-1.7.0b2.tar.gz'

#install numpy
tar -zxvf numpy-1.7.0b2.tar.gz
cd numpy-1.7.0b2
python setup.py build
python setup.py install
cd ..
python -c "import numpy; print 'Installed NumPy', numpy.__version__"
python -c "import numpy; numpy.test()"

#to be flagged by jenkins, we create an empty install dir: 
mkdir install
touch install/emptyfile

