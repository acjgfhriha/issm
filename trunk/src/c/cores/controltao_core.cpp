/*!\file: control_core.cpp
 * \brief: core of the control solution 
 */ 
#include <config.h>
#include "./cores.h"
#include "../toolkits/toolkits.h"
#include "../classes/classes.h"
#include "../shared/shared.h"
#include "../modules/modules.h"
#include "../solutionsequences/solutionsequences.h"

#if defined (_HAVE_TAO_)
#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
#include <tao.h>
#else
#include <petsctao.h>
#endif

/*Local prototype*/
#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
int FormFunctionGradient(TaoSolver,Vec,IssmDouble*,Vec,void*);
int IssmMonitor(TaoSolver,void*);
#else
int FormFunctionGradient(Tao,Vec,IssmDouble*,Vec,void*);
int IssmMonitor(Tao,void*);
#endif
typedef struct {
	FemModel* femmodel;
	double*   J;
} AppCtx;

void controltao_core(FemModel* femmodel){

	/*TAO*/
	int                 ierr;
	int                 num_controls,solution_type;
	int                 maxsteps,maxiter;
	IssmDouble          gatol,grtol,gttol;
	AppCtx              user;
	#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
	TaoSolver           tao = 0;
	#else
	Tao                 tao = 0;
	#endif
	int                *control_list = NULL;
	char               *algorithm    = NULL;
	Vector<IssmDouble> *X            = NULL;
	Vector<IssmDouble> *G            = NULL;
	Vector<IssmDouble> *XL           = NULL;
	Vector<IssmDouble> *XU           = NULL;

	/*Initialize TAO*/
	#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
	int argc; char **args=NULL;
	PetscGetArgs(&argc,&args);
	ierr = TaoInitialize(&argc,&args,(char*)0,"");
	if(ierr) _error_("Could not initialize Tao");
	#endif

	/*Recover some parameters*/
	femmodel->parameters->FindParam(&solution_type,SolutionTypeEnum);
	femmodel->parameters->FindParam(&num_controls,InversionNumControlParametersEnum);
	femmodel->parameters->FindParam(&control_list,NULL,InversionControlParametersEnum);
	femmodel->parameters->FindParam(&maxsteps,InversionMaxstepsEnum);
	femmodel->parameters->FindParam(&maxiter,InversionMaxiterEnum);
	femmodel->parameters->FindParam(&gatol,InversionGatolEnum);
	femmodel->parameters->FindParam(&grtol,InversionGrtolEnum);
	femmodel->parameters->FindParam(&gttol,InversionGttolEnum);
	femmodel->parameters->FindParam(&algorithm,InversionAlgorithmEnum);
	femmodel->parameters->SetParam(false,SaveResultsEnum);

	/*Prepare Toolkit*/
	ToolkitsOptionsFromAnalysis(femmodel->parameters,DefaultAnalysisEnum);

	/*Initialize TAO*/
	TaoCreate(IssmComm::GetComm(),&tao);
	if(VerboseControl()) _printf0_("   Initializing the Toolkit for Advanced Optimization (TAO)\n");
	TaoSetFromOptions(tao);
	TaoSetType(tao,algorithm);

	/*Prepare all TAO parameters*/
	TaoSetMonitor(tao,IssmMonitor,&user,NULL);
	TaoSetMaximumFunctionEvaluations(tao,maxiter);
	TaoSetMaximumIterations(tao,maxsteps);
	#if (_PETSC_MAJOR_==3) && (_PETSC_MINOR_<7)
	TaoSetTolerances(tao,0,0,gatol,grtol,gttol);
	#else
	TaoSetTolerances(tao,gatol,grtol,gttol);
	#endif

	GetVectorFromControlInputsx(&X, femmodel->elements,femmodel->nodes,femmodel->vertices,femmodel->loads,femmodel->materials,femmodel->parameters,"value");
	GetVectorFromControlInputsx(&XL,femmodel->elements,femmodel->nodes,femmodel->vertices,femmodel->loads,femmodel->materials,femmodel->parameters,"lowerbound");
	GetVectorFromControlInputsx(&XU,femmodel->elements,femmodel->nodes,femmodel->vertices,femmodel->loads,femmodel->materials,femmodel->parameters,"upperbound");
	TaoSetInitialVector(tao,X->pvector->vector);
	TaoSetVariableBounds(tao,XL->pvector->vector,XU->pvector->vector);
	delete XL;
	delete XU;

	user.J=xNewZeroInit<double>(maxiter+5);
	user.femmodel=femmodel;
	TaoSetObjectiveAndGradientRoutine(tao,FormFunctionGradient,(void*)&user); 

	/*Solver optimization problem*/
	if(VerboseControl()) _printf0_("   Starting optimization\n");
	TaoSolve(tao);
	TaoView(tao,PETSC_VIEWER_STDOUT_WORLD);

	/*Save results*/
	TaoGetSolutionVector(tao,&X->pvector->vector);
	G=new Vector<IssmDouble>(0); VecFree(&G->pvector->vector);
	TaoGetGradientVector(tao,&G->pvector->vector);
	SetControlInputsFromVectorx(femmodel,X);
	ControlInputSetGradientx(femmodel->elements,femmodel->nodes,femmodel->vertices,femmodel->loads,femmodel->materials,femmodel->parameters,G);
	femmodel->OutputControlsx(&femmodel->results);
	femmodel->results->AddObject(new GenericExternalResult<double*>(femmodel->results->Size()+1,JEnum,user.J,maxiter+3,1,0,0));

	/*Finalize*/
	if(VerboseControl()) _printf0_("   preparing final solution\n");
	femmodel->parameters->SetParam(true,SaveResultsEnum);
	void (*solutioncore)(FemModel*)=NULL;
	CorePointerFromSolutionEnum(&solutioncore,femmodel->parameters,solution_type);
	solutioncore(femmodel);

	/*Clean up and return*/
	xDelete<int>(control_list);
	xDelete<char>(algorithm);
	xDelete<double>(user.J);
	delete X;
	TaoDestroy(&tao);
	#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
	TaoFinalize();
	#endif
	G->pvector->vector = NULL;
	delete G;
}

#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
int FormFunctionGradient(TaoSolver tao, Vec Xpetsc, IssmDouble *fcn,Vec G,void *uservoid){
#else
int FormFunctionGradient(Tao tao, Vec Xpetsc, IssmDouble *fcn,Vec G,void *uservoid){
#endif

	/*Retreive arguments*/
	int                  solution_type;
	AppCtx              *user            = (AppCtx *)uservoid;
	FemModel            *femmodel        = user->femmodel;
	Vector<IssmDouble>  *gradient        = NULL;
	Vector<IssmDouble>  *X               = NULL;

	/*Convert input to Vec*/
	X=new Vector<IssmDouble>(Xpetsc);

	/*Set new variable*/
	//VecView(X,PETSC_VIEWER_STDOUT_WORLD);
	SetControlInputsFromVectorx(femmodel,X);
	delete X;

	/*Recover some parameters*/
	femmodel->parameters->FindParam(&solution_type,SolutionTypeEnum);

	/*Compute solution and adjoint*/
	void (*solutioncore)(FemModel*)=NULL;
	void (*adjointcore)(FemModel*)=NULL;
	CorePointerFromSolutionEnum(&solutioncore,femmodel->parameters,solution_type);
	AdjointCorePointerFromSolutionEnum(&adjointcore,solution_type);
	solutioncore(femmodel);
	adjointcore(femmodel);

	/*Compute objective function*/
	femmodel->CostFunctionx(fcn,NULL,NULL);

	/*Compute gradient*/
	Gradjx(&gradient,NULL,femmodel->elements,femmodel->nodes,femmodel->vertices,femmodel->loads,femmodel->materials,femmodel->parameters);
	VecCopy(gradient->pvector->vector,G); delete gradient;
	VecScale(G,-1.);

	/*Clean-up and return*/
	return 0;
}
#if defined (_HAVE_PETSC_) && (_PETSC_MAJOR_ == 3 && _PETSC_MINOR_ < 5)
int IssmMonitor(TaoSolver tao, void *userCtx){
#else
int IssmMonitor(Tao tao, void *userCtx){
#endif

	int         its,num_responses;
	IssmDouble  f,gnorm,cnorm,xdiff;
	AppCtx     *user      = (AppCtx *)userCtx;
	FemModel   *femmodel  = user->femmodel;
	int        *responses = NULL;

	femmodel->parameters->FindParam(&responses,&num_responses,InversionCostFunctionsEnum);

	TaoGetSolutionStatus(tao, &its, &f, &gnorm, &cnorm, &xdiff, NULL);
	if(its==0) _printf0_("Iter       Function      Residual  |  List of contributions\n");
	if(its==0) _printf0_("___________________________________________________________\n");
	_printf0_(setw(4)<<its<<"   "<<setw(12)<<setprecision(7)<<f<<"  "<<setw(12)<<setprecision(7)<<gnorm<<"  | ");
	user->J[its]=f;

	/*Retrieve objective functions independently*/
	for(int i=0;i<num_responses;i++){
		femmodel->Responsex(&f,EnumToStringx(responses[i]));
		_printf0_(" "<<setw(12)<<setprecision(7)<<f);
	}
	_printf0_("\n");

	/*Clean-up and return*/
	xDelete<int>(responses);
	return 0;
}

#else
void controltao_core(FemModel* femmodel){
	_error_("TAO not installed or PETSc version not supported");
}
#endif //_HAVE_TAO_ 
