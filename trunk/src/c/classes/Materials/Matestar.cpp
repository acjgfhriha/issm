/*!\file Matestar.c
 * \brief: implementation of the Matestar object
 */

#ifdef HAVE_CONFIG_H
	#include <config.h>
#else
#error "Cannot compile with HAVE_CONFIG_H symbol! run configure first!"
#endif

#include "./Matestar.h"
#include "./Materials.h"
#include "../Inputs/Input.h"
#include "../Inputs/Inputs.h"
#include "../Inputs/TriaInput.h"
#include "../Inputs/PentaInput.h"
#include "../Inputs/ControlInput.h"
#include "../Elements/Element.h"
#include "../Elements/Tria.h"
#include "../Elements/Penta.h"
#include "../Params/Parameters.h"
#include "../Vertex.h"
#include "../Hook.h"
#include "../Node.h"
#include "../IoModel.h"
#include "../../shared/shared.h"

/*Matestar constructors and destructor*/
Matestar::Matestar(){/*{{{*/
	this->helement=NULL;
	this->element=NULL;
	return;
}
/*}}}*/
Matestar::Matestar(int matestar_mid,int index, IoModel* iomodel){/*{{{*/

	/*Intermediaries:*/
	int    matestar_eid;

	/*Initialize id*/
	this->mid=matestar_mid;

	/*Hooks: */
	matestar_eid=index+1;
	this->helement=new Hook(&matestar_eid,1);
	this->element=NULL;

	return;
}
/*}}}*/
Matestar::~Matestar(){/*{{{*/
	delete helement;
	return;
}
/*}}}*/

/*Object virtual functions definitions:*/
Object*   Matestar::copy() {/*{{{*/

	/*Output*/
	Matestar* matestar=NULL;

	/*Initialize output*/
	matestar=new Matestar();

	/*copy fields: */
	matestar->mid=this->mid;
	matestar->helement=(Hook*)this->helement->copy();
	matestar->element =(Element*)this->helement->delivers();

	return matestar;
}
/*}}}*/
Material* Matestar::copy2(Element* element_in) {/*{{{*/

	/*Output*/
	Matestar* matestar=NULL;

	/*Initialize output*/
	matestar=new Matestar();

	/*copy fields: */
	matestar->mid=this->mid;
	matestar->helement=(Hook*)this->helement->copy();
	matestar->element =element_in;

	return matestar;
}
/*}}}*/
void      Matestar::DeepEcho(void){/*{{{*/

	_printf_("Matestar:\n");
	_printf_("   mid: " << mid << "\n");
	_printf_("   element:\n");
	helement->Echo();
}		
/*}}}*/
void      Matestar::Echo(void){/*{{{*/

	_printf_("Matestar:\n");
	_printf_("   mid: " << mid << "\n");
	_printf_("   element:\n");
	helement->Echo();
}
/*}}}*/
int       Matestar::Id(void){ return mid; }/*{{{*/
/*}}}*/
void      Matestar::Marshall(char** pmarshalled_data,int* pmarshalled_data_size, int marshall_direction){ /*{{{*/

	if(marshall_direction==MARSHALLING_BACKWARD)helement=new Hook(); 
	
	MARSHALLING_ENUM(MatestarEnum);
	MARSHALLING(mid);
	this->helement->Marshall(pmarshalled_data,pmarshalled_data_size,marshall_direction);
	this->element=(Element*)this->helement->delivers();

}
/*}}}*/
int       Matestar::ObjectEnum(void){/*{{{*/

	return MatestarEnum;

}
/*}}}*/

/*Matestar management*/
void  Matestar::Configure(Elements* elementsin){/*{{{*/

	/*Take care of hooking up all objects for this element, ie links the objects in the hooks to their respective 
	 * datasets, using internal ids and offsets hidden in hooks: */
	helement->configure((DataSet*)elementsin);
	this->element  = (Element*)helement->delivers();
}
/*}}}*/
IssmDouble Matestar::GetA(){/*{{{*/
	/*
	 * A = 1/B^n
    */

	IssmDouble B,n;

	element->inputs->GetInputAverage(&B,MaterialsRheologyBEnum);
	n=this->GetN();

	return pow(B,-n);
}
/*}}}*/
IssmDouble Matestar::GetAbar(){/*{{{*/
	/*
	 * A = 1/B^n
	 */

	IssmDouble B,n;

	element->inputs->GetInputAverage(&B,MaterialsRheologyBbarEnum);
	n=this->GetN();

	return pow(B,-n);
}
/*}}}*/
IssmDouble Matestar::GetB(){/*{{{*/

	/*Output*/
	IssmDouble B;

	element->inputs->GetInputAverage(&B,MaterialsRheologyBEnum);
	return B;
}
/*}}}*/
IssmDouble Matestar::GetBbar(){/*{{{*/

	/*Output*/
	IssmDouble Bbar;

	element->inputs->GetInputAverage(&Bbar,MaterialsRheologyBbarEnum);
	return Bbar;
}
/*}}}*/
IssmDouble Matestar::GetD(){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
IssmDouble Matestar::GetDbar(){/*{{{*/

	_error_("not implemented yet");
}
/*}}}*/
IssmDouble Matestar::GetEc(){/*{{{*/

	/*Output*/
	IssmDouble Ec;

	element->inputs->GetInputAverage(&Ec,MaterialsRheologyEcEnum);
	return Ec;
}
/*}}}*/
IssmDouble Matestar::GetEcbar(){/*{{{*/

	/*Output*/
	IssmDouble Ecbar;

	element->inputs->GetInputAverage(&Ecbar,MaterialsRheologyEcbarEnum);
	return Ecbar;
}
/*}}}*/
IssmDouble Matestar::GetEs(){/*{{{*/

	/*Output*/
	IssmDouble Es;

	element->inputs->GetInputAverage(&Es,MaterialsRheologyEsEnum);
	return Es;
}
/*}}}*/
IssmDouble Matestar::GetEsbar(){/*{{{*/

	/*Output*/
	IssmDouble Esbar;

	element->inputs->GetInputAverage(&Esbar,MaterialsRheologyEsbarEnum);
	return Esbar;
}
/*}}}*/
IssmDouble Matestar::GetN(){/*{{{*/

	/*Output*/
	IssmDouble n=3.0;
	return n;
}
/*}}}*/
void  Matestar::GetViscosity(IssmDouble* pviscosity,IssmDouble eps_eff){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosityBar(IssmDouble* pviscosity,IssmDouble eps_eff){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosityComplement(IssmDouble* pviscosity_complement, IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosityDComplement(IssmDouble* pviscosity_complement, IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosityDerivativeEpsSquare(IssmDouble* pmu_prime, IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
IssmDouble Matestar::GetViscosityGeneral(IssmDouble vx,IssmDouble vy,IssmDouble vz,IssmDouble* dvx,IssmDouble* dvy,IssmDouble* dvz,bool isdepthaveraged){/*{{{*/

	/*output: */
	IssmDouble viscosity;

	/*Intermediaries*/
	IssmDouble epseff,epsprime_norm;
	IssmDouble lambdas;
	IssmDouble vmag,dvmag[3];
	IssmDouble B,Ec,Es,E,n;

	/*Calculate velocity magnitude and its derivative*/
	vmag = sqrt(vx*vx+vy*vy+vz*vz);
	if(vmag<1e-12){
		dvmag[0]=0;
		dvmag[1]=0;
		dvmag[2]=0;
	}
	else{
		dvmag[0]=1./(2*sqrt(vmag))*(2*vx*dvx[0]+2*vy*dvy[0]+2*vz*dvz[0]);
		dvmag[1]=1./(2*sqrt(vmag))*(2*vx*dvx[1]+2*vy*dvy[1]+2*vz*dvz[1]);
		dvmag[2]=1./(2*sqrt(vmag))*(2*vx*dvx[2]+2*vy*dvy[2]+2*vz*dvz[2]);
	}

	EstarStrainrateQuantities(&epseff,&epsprime_norm,vx,vy,vz,vmag,dvx,dvy,dvz,&dvmag[0]);
	lambdas=EstarLambdaS(epseff,epsprime_norm);

	/*Get B and enhancement*/
	n=GetN(); _assert_(n>0.);
	if (isdepthaveraged==0.){
		B=GetB(); _assert_(B>0.);
		Ec=GetEc(); _assert_(Ec>=0.);
		Es=GetEs(); _assert_(Es>=0.);
	}
	else{
		B=GetBbar(); _assert_(B>0.);
		Ec=GetEcbar(); _assert_(Ec>=0.);
		Es=GetEsbar(); _assert_(Es>=0.);
	}

	/*Get total enhancement factor E(lambdas)*/
	E = Ec + (Es-Ec)*lambdas*lambdas; _assert_(E>0.);

	/*Compute viscosity*/
	/*if no strain rate, return maximum viscosity*/
	if(epseff==0.){
		viscosity = 1.e+14/2.;
		//viscosity = B;
		//viscosity=2.5*pow(10.,17);
	}
	else{
		viscosity = B/(2.*pow(E,1./n)*pow(epseff,2./n));
	}

	/*Assign output pointer*/
	return viscosity;
}
/*}}}*/
IssmDouble Matestar::GetViscosity_BGeneral(IssmDouble vx,IssmDouble vy,IssmDouble vz,IssmDouble* dvx,IssmDouble* dvy,IssmDouble* dvz,bool isdepthaveraged){/*{{{*/

	/*Intermediaries*/
	IssmDouble dmudB;
	IssmDouble epseff,epsprime_norm;
	IssmDouble lambdas;
	IssmDouble vmag,dvmag[3];
	IssmDouble Ec,Es,E;

	/*Calculate velocity magnitude and its derivative*/
	vmag = sqrt(vx*vx+vy*vy+vz*vz);
	if(vmag<1e-12){
		dvmag[0]=0;
		dvmag[1]=0;
		dvmag[2]=0;
	}
	else{
		dvmag[0]=1./(2*sqrt(vmag))*(2*vx*dvx[0]+2*vy*dvy[0]+2*vz*dvz[0]);
		dvmag[1]=1./(2*sqrt(vmag))*(2*vx*dvx[1]+2*vy*dvy[1]+2*vz*dvz[1]);
		dvmag[2]=1./(2*sqrt(vmag))*(2*vx*dvx[2]+2*vy*dvy[2]+2*vz*dvz[2]);
	}

	EstarStrainrateQuantities(&epseff,&epsprime_norm,vx,vy,vz,vmag,dvx,dvy,dvz,&dvmag[0]);
	lambdas=EstarLambdaS(epseff,epsprime_norm);

	/*Get enhancement*/
	if (isdepthaveraged==0.){
		Ec=GetEc(); _assert_(Ec>=0.);
		Es=GetEs(); _assert_(Es>=0.);
	}
	else{
		Ec=GetEcbar(); _assert_(Ec>=0.);
		Es=GetEsbar(); _assert_(Es>=0.);
	}

	/*Get total enhancement factor E(lambdas)*/
	E = Ec + (Es-Ec)*lambdas*lambdas; _assert_(E>0.);

	/*Compute dmudB*/
	if(epseff==0.) dmudB = 0.;
	else           dmudB = 1./(2.*pow(E,1./3.)*pow(epseff,2./3.));

	/*Assign output*/
	return dmudB;

}
/*}}}*/
void  Matestar::GetViscosity_B(IssmDouble* pdmudB,IssmDouble eps_eff){/*{{{*/
	 _error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosity_D(IssmDouble* pdmudD,IssmDouble eps_eff){/*{{{*/
	 _error_("not implemented yet");
}
/*}}}*/
void  Matestar::GetViscosity2dDerivativeEpsSquare(IssmDouble* pmu_prime, IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::InputUpdateFromConstant(IssmDouble constant, int name){/*{{{*/
	/*Nothing updated yet*/
}
/*}}}*/
void  Matestar::InputUpdateFromConstant(int constant, int name){/*{{{*/
	/*Nothing updated yet*/
}
/*}}}*/
void  Matestar::InputUpdateFromConstant(bool constant, int name){/*{{{*/
	/*Nothing updated yet*/
}
/*}}}*/
void  Matestar::InputUpdateFromMatrixDakota(IssmDouble* matrix, int nrows, int ncols,int name, int type){/*{{{*/
	/*Nothing updated yet*/
}
/*}}}*/
void  Matestar::InputUpdateFromVector(IssmDouble* vector, int name, int type){/*{{{*/

}
/*}}}*/
void  Matestar::InputUpdateFromVectorDakota(IssmDouble* vector, int name, int type){/*{{{*/

}
/*}}}*/
bool Matestar::IsDamage(){/*{{{*/

	_error_("not implemented yet");
}
/*}}}*/
void  Matestar::ResetHooks(){/*{{{*/

	this->element=NULL;

	/*Get Element type*/
	this->helement->reset();

}
/*}}}*/
void  Matestar::SetCurrentConfiguration(Elements* elementsin,Loads* loadsin,Nodes* nodesin,Vertices* verticesin,Materials* materialsin,Parameters* parametersin){/*{{{*/

}
/*}}}*/
void  Matestar::ViscosityBFS(IssmDouble* pdmudB,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input,Input* vz_input){/*{{{*/

	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=0.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim>1);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	_assert_(vy_input);
	vy_input->GetInputValue(&vy,gauss);
	vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	if(dim==3){
		_assert_(vz_input);
		vz_input->GetInputValue(&vz,gauss);
		vz_input->GetInputDerivativeValue(&dvz[0],xyz_list,gauss);
	}
	else{
		vz = 0.;
		dvz[0] = 0.; dvz[1] = 0.; dvz[2] = 0.;
	}

	/*Compute dmudB*/
	*pdmudB=GetViscosity_BGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}
/*}}}*/
void  Matestar::ViscosityBHO(IssmDouble* pdmudB,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input){/*{{{*/

	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=0.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim==2 || dim==3);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	if(dim==3){
		_assert_(vy_input);
		vy_input->GetInputValue(&vy,gauss);
		vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	}
	else{
		dvx[2] = 0.;
		vy = 0.;
		dvy[0] = 0.; dvy[1] = 0.; dvy[2] = 0.;
	}
	vz = 0.;
	dvz[0] = 0.; dvz[1] = 0.; dvz[2] = -dvx[0]-dvy[1];

	/*Compute viscosity*/
	*pdmudB=GetViscosity_BGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}/*}}}*/
void  Matestar::ViscosityBSSA(IssmDouble* pdmudB,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input){/*{{{*/
	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=1.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim==1 || dim==2);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	if(dim==2){
		_assert_(vy_input);
		vy_input->GetInputValue(&vy,gauss);
		vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	}
	else{
		dvx[1] = 0.;
		dvx[2] = 0.;
		vy = 0.;
		dvy[0] = 0.; dvy[1] = 0.; dvy[2] = 0.;
	}
	dvx[2] = 0.;
	dvy[2] = 0.;
	vz = 0.;
	dvz[0] = 0.; dvz[1] = 0.; dvz[2] = -dvx[0]-dvy[1];

	/*Compute viscosity*/
	*pdmudB=GetViscosity_BGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}/*}}}*/
void  Matestar::ViscosityFS(IssmDouble* pviscosity,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input,Input* vz_input){/*{{{*/

	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=0.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim>1);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	_assert_(vy_input);
	vy_input->GetInputValue(&vy,gauss);
	vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	if(dim==3){
		_assert_(vz_input);
		vz_input->GetInputValue(&vz,gauss);
		vz_input->GetInputDerivativeValue(&dvz[0],xyz_list,gauss);
	}
	else{
		vz = 0.;
		dvz[0] = 0.; dvz[1] = 0.; dvz[2] = 0.;
	}

	/*Compute viscosity*/
	*pviscosity=GetViscosityGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}
/*}}}*/
void  Matestar::ViscosityFSDerivativeEpsSquare(IssmDouble* pmu_prime,IssmDouble* epsilon){/*{{{*/
	this->GetViscosityDerivativeEpsSquare(pmu_prime,epsilon);
}/*}}}*/
void  Matestar::ViscosityHO(IssmDouble* pviscosity,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input){/*{{{*/

	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=0.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim==2 || dim==3);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	if(dim==3){
		_assert_(vy_input);
		vy_input->GetInputValue(&vy,gauss);
		vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	}
	else{
		dvx[2] = 0.;
		vy = 0.;
		dvy[0] = 0.; dvy[1] = 0.; dvy[2] = 0.;
	}
	vz = 0.;
	dvz[0] = 0.; dvz[1] = 0.; dvz[2] = -dvx[0]-dvy[1];

	/*Compute viscosity*/
	*pviscosity=GetViscosityGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}/*}}}*/
void  Matestar::ViscosityHODerivativeEpsSquare(IssmDouble* pmu_prime,IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}/*}}}*/
void  Matestar::ViscosityL1L2(IssmDouble* pviscosity,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input,Input* surface_input){/*{{{*/
	_error_("not implemented yet");
}/*}}}*/
void  Matestar::ViscositySSA(IssmDouble* pviscosity,int dim,IssmDouble* xyz_list,Gauss* gauss,Input* vx_input,Input* vy_input){/*{{{*/

	/*Intermediaries*/
	IssmDouble vx,vy,vz;
	IssmDouble dvx[3],dvy[3],dvz[3];
	bool isdepthaveraged=1.;

	/*Get velocity derivatives in all directions*/
	_assert_(dim==1 || dim==2);
	_assert_(vx_input);
	vx_input->GetInputValue(&vx,gauss);
	vx_input->GetInputDerivativeValue(&dvx[0],xyz_list,gauss);
	if(dim==2){
		_assert_(vy_input);
		vy_input->GetInputValue(&vy,gauss);
		vy_input->GetInputDerivativeValue(&dvy[0],xyz_list,gauss);
	}
	else{
		dvx[1] = 0.;
		dvx[2] = 0.;
		vy = 0.;
		dvy[0] = 0.; dvy[1] = 0.; dvy[2] = 0.;
	}
	dvx[2] = 0.;
	dvy[2] = 0.;
	vz = 0.;
	dvz[0] = 0.; dvz[1] = 0.; dvz[2] = -dvx[0]-dvy[1];

	/*Compute viscosity*/
	*pviscosity=GetViscosityGeneral(vx,vy,vz,&dvx[0],&dvy[0],&dvz[0],isdepthaveraged);
}/*}}}*/
void  Matestar::ViscositySSADerivativeEpsSquare(IssmDouble* pmu_prime,IssmDouble* epsilon){/*{{{*/
	_error_("not implemented yet");
}/*}}}*/
