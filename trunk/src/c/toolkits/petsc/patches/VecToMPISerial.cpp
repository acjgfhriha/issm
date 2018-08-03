/*!\file VecToMPISerial.cpp
 * \brief gather a Petsc Vector spread across the cluster, onto node 0, and then broadcast to all nodes. 
 */

#ifdef HAVE_CONFIG_H
	#include <config.h>
#else
#error "Cannot compile with HAVE_CONFIG_H symbol! run configure first!"
#endif

#include "../petscincludes.h"
#include "../../../shared/shared.h"

int VecToMPISerial(double** pgathered_vector, Vec vector,ISSM_MPI_Comm comm){

	int i;
	int num_procs; 
	int my_rank;

	/*Petsc*/
	ISSM_MPI_Status status;
	PetscInt lower_row,upper_row; 
	int range;
	int * idxn=NULL; 
	int buffer[3];

	/*intermediary results*/
	double* local_vector=NULL;

	/*input*/
	int vector_size;

	/*Output*/
	double* gathered_vector=NULL; //Global vector holding the final assembled vector on all nodes.

	/*recover my_rank and num_procs*/
	ISSM_MPI_Comm_size(comm,&num_procs);
	ISSM_MPI_Comm_rank(comm,&my_rank);

	VecGetSize(vector,&vector_size);
	if(vector_size==0){
		*pgathered_vector=NULL;
		return 1;
	}

	/*Allocate gathered vector on all nodes .*/
	gathered_vector=xNew<double>(vector_size);

	/*Allocate local vectors*/
	VecGetOwnershipRange(vector,&lower_row,&upper_row);
	upper_row--;
	range=upper_row-lower_row+1;    

	if (range){
		idxn=xNew<int>(range); 
		for (i=0;i<range;i++){
			*(idxn+i)=lower_row+i;
		} 
		local_vector=xNew<double>(range);
		/*Extract values from MPI vector to serial local_vector on each node*/
		VecGetValues(vector,range,idxn,local_vector); 
	}

	/*Now each node holds its local_vector containing range rows. 
	 * We send this local_vector  to the gathered_vector on node 0*/
	for (i=1;i<num_procs;i++){
		if (my_rank==i){ 
			buffer[0]=my_rank;
			buffer[1]=lower_row;
			buffer[2]=range;
			ISSM_MPI_Send(buffer,3,ISSM_MPI_INT,0,1,comm);  
			if (range)ISSM_MPI_Send(local_vector,range,ISSM_MPI_PDOUBLE,0,1,comm); 
		}
		if (my_rank==0){
			ISSM_MPI_Recv(buffer,3,ISSM_MPI_INT,i,1,comm,&status); 
			if (buffer[2])ISSM_MPI_Recv(gathered_vector+buffer[1],buffer[2],ISSM_MPI_PDOUBLE,i,1,comm,&status);
		}
	}

	if (my_rank==0){ 
		//Still have the local_vector on node 0 to take care of.
		if (range)memcpy(gathered_vector+lower_row,local_vector,range*sizeof(double));
	}

	/*Now, broadcast gathered_vector from node 0 to other nodes: */
	ISSM_MPI_Bcast(gathered_vector,vector_size,ISSM_MPI_PDOUBLE,0,comm);

	/*Assign output pointers: */
	*pgathered_vector=gathered_vector;

	/*free ressources: */
	xDelete<int>(idxn);
	xDelete<double>(local_vector);

	return 1;
}
