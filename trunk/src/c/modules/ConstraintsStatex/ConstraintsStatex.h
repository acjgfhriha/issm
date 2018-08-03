/*!\file:  ConstraintsStatex.h
 * \brief header file for penalty constraints module
 */ 

#ifndef _CONSTRAINTSSTATEX_H
#define _CONSTRAINTSSTATEX_H

#include "../../classes/classes.h"

/* local prototypes: */
int  RiftIsPresent(Loads* loads,int analysis_type);
void ConstraintsStatex(int* pconverged, int* pnum_unstable_constraints,FemModel* femmodel);

#endif  /* _CONSTRAINTSSTATEX_H */
