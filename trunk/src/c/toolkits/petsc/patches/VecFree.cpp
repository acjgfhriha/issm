/*!\file:  VecFree.cpp
 * \brief wrapper to VecDestroy
 */ 

#ifdef HAVE_CONFIG_H
	#include <config.h>
#else
#error "Cannot compile with HAVE_CONFIG_H symbol! run configure first!"
#endif

/*Petsc includes: */
#include <petscmat.h>
#include <petscvec.h>
#include <petscksp.h>

void VecFree(Vec* pvec){

	#if _PETSC_MAJOR_ < 3 || (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 2)
	if(*pvec)VecDestroy(*pvec);
	#else
	if(*pvec)VecDestroy(pvec);
	#endif
	*pvec=NULL;

}
