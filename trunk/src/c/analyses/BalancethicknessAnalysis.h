/*! \file BalancethicknessAnalysis.h 
 *  \brief: header file for generic external result object
 */

#ifndef _BalancethicknessAnalysis_
#define _BalancethicknessAnalysis_

/*Headers*/
#include "./Analysis.h"

class BalancethicknessAnalysis: public Analysis{

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
		ElementMatrix* CreateKMatrixCG(Element* element);
		ElementMatrix* CreateKMatrixDG(Element* element);
		ElementVector* CreatePVector(Element* element);
		ElementVector* CreatePVectorCG(Element* element);
		ElementVector* CreatePVectorDG(Element* element);
		void           GetB(IssmDouble* B,Element* element,IssmDouble* xyz_list,Gauss* gauss);
		void           GetBprime(IssmDouble* B,Element* element,IssmDouble* xyz_list,Gauss* gauss);
		void           GetSolutionFromInputs(Vector<IssmDouble>* solution,Element* element);
		void           GradientJ(Vector<IssmDouble>* gradient,Element* element,int control_type,int control_index);
		void           InputUpdateFromSolution(IssmDouble* solution,Element* element);
		void           UpdateConstraints(FemModel* femmodel);
};
#endif
