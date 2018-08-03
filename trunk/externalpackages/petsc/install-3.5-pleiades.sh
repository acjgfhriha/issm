#!/bin/bash
set -eu

#Some cleanup
rm -rf install petsc-3.5.3 src
mkdir install src

#Download from ISSM server
$ISSM_DIR/scripts/DownloadExternalPackage.py 'http://issm.jpl.nasa.gov/files/externalpackages/petsc-lite-3.5.3.tar.gz' 'petsc-3.5.3.tar.gz'

#Untar and move petsc to install directory
tar -zxvf  petsc-3.5.3.tar.gz
mv petsc-3.5.3/* src/
rm -rf petsc-3.5.3

#configure
cd src
./config/configure.py \
	--prefix="$ISSM_DIR/externalpackages/petsc/install" \
	--PETSC_DIR="$ISSM_DIR/externalpackages/petsc/src" \
	--with-blas-lapack-dir="/nasa/intel/Compiler/2015.0.090/composer_xe_2015.0.090/mkl/" \
	--with-mpi-lib="/nasa/sgi/mpt/2.11r13/lib/libmpi.so" \
	--with-mpi-include="/nasa/sgi/mpt/2.11r13/include" \
	--known-mpi-shared-libraries=1 \
	--with-debugging=0 \
	--with-valgrind=0 \
	--with-x=0 \
	--with-ssl=0 \
	--with-batch=1  \
	--with-shared-libraries=1 \
	--download-metis=1 \
	--download-parmetis=1 \
	--download-mumps=1 \
	--download-scalapack=1 \
	--download-fblaslapack=1

#prepare script to reconfigure petsc
cat > script.queue << EOF
#PBS -S /bin/bash
#PBS -l select=1:ncpus=1:model=wes 
#PBS -l walltime=200 
#PBS -W group_list=s1010
#PBS -m e 

. /usr/share/modules/init/bash 
module load comp-intel/2015.0.090
module load mpi-sgi/mpt.2.11r13

export PATH="$PATH:." 
export MPI_GROUP_MAX=64 
mpiexec -np 1 ./conftest-arch-linux2-c-opt
EOF

#print instructions
echo "== Now: cd src/ "
echo "== qsub -q devel script.queue "
echo "== Then run reconfigure script generated by PETSc and follow instructions"