/*
	PointCloudFindNeighbors.h
*/

#ifndef _POINTCLOUDFINDNEIGHBORS_H
#define _POINTCLOUDFINDNEIGHBORS_H

#ifdef HAVE_CONFIG_H
	#include <config.h>
#else
	#error "Cannot compile with HAVE_CONFIG_H symbol! run configure first!"
#endif

/*For python modules: needs to come before header files inclusion*/
#ifdef _HAVE_PYTHON_
#define PY_ARRAY_UNIQUE_SYMBOL PythonIOSymbol
#endif

#include "../bindings.h"
#include "../../c/main/globals.h"
#include "../../c/modules/modules.h"
#include "../../c/shared/shared.h"

#undef __FUNCT__
#define __FUNCT__ "PointCloudFindNeighbors"

#ifdef _HAVE_MATLAB_MODULES_
/* input macros: */
#define XHANDLE     prhs[0]
#define YHANDLE     prhs[1]
#define MINDISTANCE prhs[2]
#define MULTITHREAD prhs[3]
/* serial output macros: */
#define FLAGS (mxArray**)&plhs[0]
#endif

#ifdef _HAVE_PYTHON_MODULES_
/* input macros: */
#define XHANDLE     PyTuple_GetItem(args,0)
#define YHANDLE     PyTuple_GetItem(args,1)
#define MINDISTANCE PyTuple_GetItem(args,2)
#define MULTITHREAD PyTuple_GetItem(args,3)
/* serial output macros: */
#define FLAGS output,0
#endif

/* serial arg counts: */
#undef NLHS
#define NLHS 1
#undef NRHS
#define NRHS 4

#endif  /* _POINTCLOUDFINDNEIGHBORS_H */
