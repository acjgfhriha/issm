/*! \file ExtrapolationAnalysis.h 
 *  \brief: header file for generic external result object
 */

#ifndef _ExtrapolationAnalysis_
#define _ExtrapolationAnalysis_

/*Headers*/
#include "./Analysis.h"

class ExtrapolationAnalysis: public Analysis{
	
 public:
	/*Model processing*/
	void CreateConstraints(Constraints* constraints,IoModel* iomodel);
	void CreateLoads(Loads* loads, IoModel* iomodel);
	void CreateNodes(Nodes* nodes,IoModel* iomodel);
	int  DofsPerNode(int** doflist,int domaintype,int approximation);
	void UpdateElements(Elements* elements,IoModel* iomodel,int analysis_counter,int analysis_type);
	void UpdateParameters(Parameters* parameters,IoModel* iomodel,int solution_enum,int analysis_enum);

	/*Finite element Analysis*/
	void           Core(FemModel* femmodel);
	ElementVector* CreateDVector(Element* element);
	ElementMatrix* CreateJacobianMatrix(Element* element);
	ElementMatrix* CreateKMatrix(Element* element);
	ElementVector* CreatePVector(Element* element);
	void           GetB(IssmDouble* B,Element* element,IssmDouble* xyz_list,Gauss* gauss, int dim);
	void           GetBprime(IssmDouble* Bprime,Element* element,IssmDouble* xyz_list,Gauss* gauss, int dim);
	void           GetSolutionFromInputs(Vector<IssmDouble>* solution,Element* element);
	void           GradientJ(Vector<IssmDouble>* gradient,Element* element,int control_type,int control_index);
	void           InputUpdateFromSolution(IssmDouble* solution,Element* element);
	int				GetExtrapolationCase(Element* element);
	void           SetConstraintsOnIce(Element* element);
	void           UpdateConstraints(FemModel* femmodel);
};
#endif
