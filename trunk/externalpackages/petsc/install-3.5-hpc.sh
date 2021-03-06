#!/bin/bash
set -eu

#WARNING: make sure you have the right mpi:

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
 --with-mpi-dir="/data/apps/mpi/openmpi-1.8.3/gcc/4.8.3/" \
 --known-mpi-shared-libraries=1 \
 --with-debugging=0 \
 --with-valgrind=0 \
 --with-x=0 \
 --with-ssl=0 \
 --with-batch=1  \
 --with-shared-libraries=1 \
 --download-metis=1 \
 --download-parmetis=1 \
 --download-scalapack=1 \
 --download-fblaslapack=1 \
 --download-mumps=1 

#prepare script to reconfigure petsc
cat > script.queue << EOF
#!/bin/bash
#$ -N PETSC
#$ -q free*,pub64

cd $(echo $ISSM_DIR)/externalpackages/petsc/src/
mpiexec -np 1 ./conftest-arch-linux2-c-opt
EOF

#print instructions
echo "== Now: cd src/ "
echo "== qsub script.queue "
echo "== Then run reconfigure script generated by PETSc and follow instructions"
