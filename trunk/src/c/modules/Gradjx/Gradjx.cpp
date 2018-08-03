/*!\file Gradjx
 * \brief: compute inverse method gradient
 */

#include "./Gradjx.h"
#include "../../shared/shared.h"
#include "../../toolkits/toolkits.h"

void Gradjx(Vector<IssmDouble>** pgradient,IssmDouble** pnorm_list, Elements* elements,Nodes* nodes, Vertices* vertices, Loads* loads, Materials* materials, Parameters* parameters){

	int          numberofvertices;
	int          num_controls,analysisenum;
	IssmDouble   norm_inf;
	IssmDouble  *norm_list     = NULL;
	int     *control_type  = NULL;
	Vector<IssmDouble>  *gradient      = NULL;
	Vector<IssmDouble> **gradient_list = NULL;

	/*Display message*/
	if(VerboseModule()) _printf0_("   Computing cost function gradient\n");

	/*retrieve some parameters: */
	parameters->FindParam(&num_controls,InversionNumControlParametersEnum);   _assert_(num_controls);
	parameters->FindParam(&control_type,NULL,InversionControlParametersEnum);
	numberofvertices=vertices->NumberOfVertices();

	/*Get current analysis*/
	parameters->FindParam(&analysisenum,AnalysisTypeEnum);
	Analysis* analysis = EnumToAnalysis(analysisenum);

	/*Allocate gradient_list */
	gradient_list = xNew<Vector<IssmDouble>*>(num_controls);
	norm_list = xNew<IssmDouble>(num_controls);
	for(int i=0;i<num_controls;i++){
		gradient_list[i]=new Vector<IssmDouble>(num_controls*numberofvertices);
	}
	gradient=new Vector<IssmDouble>(num_controls*numberofvertices);

	/*Compute all gradient_list*/
	for(int i=0;i<num_controls;i++){
		for(int j=0;j<elements->Size();j++){
			Element* element=(Element*)elements->GetObjectByOffset(j);
			analysis->GradientJ(gradient_list[i],element,control_type[i],i);
		}
		gradient_list[i]->Assemble();
		norm_list[i]=gradient_list[i]->Norm(NORM_INF);
	}

	/*Add all gradient_list together*/
	for(int i=0;i<num_controls;i++){
		gradient->AXPY(gradient_list[i],1.0);
		delete gradient_list[i];
	}

	/*Check that gradient is clean*/
	norm_inf=gradient->Norm(NORM_INF);
	if(norm_inf<=0)                 _error_("||dJ/dk|| = 0    gradient norm is zero");
	if(xIsNan<IssmDouble>(norm_inf))_error_("||dJ/dk|| = NaN  gradient norm is NaN");

	/*Clean-up and assign output pointer*/
	delete analysis;
	xDelete<Vector<IssmDouble>*>(gradient_list);
	xDelete<int>(control_type);
	if(pnorm_list){
		*pnorm_list=norm_list;
	}
	else{
		xDelete<IssmDouble>(norm_list);
	}
	if(pgradient)  *pgradient=gradient;

}
void Gradjx(IssmDouble** pgradient,IssmDouble** pnorm_list, Elements* elements,Nodes* nodes, Vertices* vertices, Loads* loads, Materials* materials, Parameters* parameters){

	/*output: */
	IssmDouble* gradient=NULL;

	/*intermediary: */
	Vector<IssmDouble>* vec_gradient=NULL;

	Gradjx(&vec_gradient,pnorm_list,elements,nodes, vertices,loads,materials,parameters);
	gradient=vec_gradient->ToMPISerial();

	/*Free ressources:*/
	delete vec_gradient;

	/*Assign output pointers:*/
	*pgradient=gradient;
}
