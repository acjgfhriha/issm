/*!\file:  adjointstressbalance_core.cpp
 * \brief compute inverse method adjoint state
 */ 

#include "./cores.h"
#include "../toolkits/toolkits.h"
#include "../classes/classes.h"
#include "../shared/shared.h"
#include "../modules/modules.h"
#include "../solutionsequences/solutionsequences.h"

void adjointstressbalance_core(FemModel* femmodel){

	/*parameters: */
	bool isFS;
	bool save_results;
	bool conserve_loads   = true;
	int fe_FS;

	/*retrieve parameters:*/
	femmodel->parameters->FindParam(&isFS,FlowequationIsFSEnum);
	femmodel->parameters->FindParam(&save_results,SaveResultsEnum);
	femmodel->parameters->FindParam(&fe_FS,FlowequationFeFSEnum);

	/*Compute velocities*/
	if(VerboseSolution()) _printf0_("   computing velocities\n");
	femmodel->SetCurrentConfiguration(StressbalanceAnalysisEnum);

	if(VerboseSolution()) _printf0_("   computing velocities\n");
	femmodel->SetCurrentConfiguration(StressbalanceAnalysisEnum);
	if(isFS){
		if (fe_FS==LATaylorHoodEnum || fe_FS==LACrouzeixRaviartEnum)
		 solutionsequence_la(femmodel);
		else
		 solutionsequence_nonlinear(femmodel,conserve_loads); 
	}
	else{
		solutionsequence_nonlinear(femmodel,conserve_loads); 
	}

	/*Call SurfaceAreax, because some it might be needed by PVector*/
	SurfaceAreax(NULL,femmodel);

	/*Compute adjoint*/
	if(VerboseSolution()) _printf0_("   computing adjoint\n");
	femmodel->SetCurrentConfiguration(StressbalanceAnalysisEnum,AdjointHorizAnalysisEnum);
	solutionsequence_adjoint_linear(femmodel);

	/*Save results*/
	if(save_results || true){
		if(VerboseSolution()) _printf0_("   saving results\n");
		if(isFS){
			if(fe_FS==LATaylorHoodEnum || fe_FS==LACrouzeixRaviartEnum){
				int outputs[2] = {AdjointxEnum,AdjointyEnum};
				femmodel->RequestedOutputsx(&femmodel->results,&outputs[0],2);
			}
			else{
				int outputs[3] = {AdjointxEnum,AdjointyEnum,AdjointpEnum};
				femmodel->RequestedOutputsx(&femmodel->results,&outputs[0],3);
			}
		}
		else{
			int outputs[2] = {AdjointxEnum,AdjointyEnum};
			femmodel->RequestedOutputsx(&femmodel->results,&outputs[0],2);
		}
	}
}
