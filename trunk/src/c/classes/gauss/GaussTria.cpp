/*!\file GaussTria.c
 * \brief: implementation of the GaussTria object
 */

#include "./GaussTria.h"
#include "../../shared/shared.h"

/*GaussTria constructors and destructors:*/
GaussTria::GaussTria(){/*{{{*/

	numgauss=-1;

	weights=NULL;
	coords1=NULL;
	coords2=NULL;
	coords3=NULL;

	weight=UNDEF;
	coord1=UNDEF;
	coord2=UNDEF;
	coord3=UNDEF;
}
/*}}}*/
GaussTria::GaussTria(int order){/*{{{*/

	/*Get gauss points*/
	GaussLegendreTria(&numgauss,&coords1,&coords2,&coords3,&weights,order);

	/*Initialize static fields as undefinite*/
	weight=UNDEF;
	coord1=UNDEF;
	coord2=UNDEF;
	coord3=UNDEF;

}
/*}}}*/
GaussTria::GaussTria(int index1,int index2,int order){/*{{{*/

	/*Intermediaties*/
	IssmPDouble *seg_coords  = NULL;
	IssmPDouble *seg_weights = NULL;
	IssmDouble  a1,b1,c1,a2,b2,c2;

	/*Get Segment gauss points*/
	numgauss=order;
	GaussLegendreLinear(&seg_coords,&seg_weights,numgauss);

	/*Allocate GaussTria fields*/
	coords1=xNew<IssmDouble>(numgauss);
	coords2=xNew<IssmDouble>(numgauss);
	coords3=xNew<IssmDouble>(numgauss);
	weights=xNew<IssmDouble>(numgauss);

	/*Figure out coords of index1 (a1,b1,c1) and index2 (a2,b2,c2)*/
	if(index1==0){
		a1=1; b1=0; c1=0;
	}
	else if(index1==1){
		a1=0; b1=1; c1=0;
	}
	else if(index1==2){
		a1=0; b1=0; c1=1;
	}
	else{
		_error_("First indice provided is not supported yet (user provided " << index1 << ")");
	}
	if(index2==0){
		a2=1; b2=0; c2=0;
	}
	else if(index2==1){
		a2=0; b2=1; c2=0;
	}
	else if(index2==2){
		a2=0; b2=0; c2=1;
	}
	else{
	 _error_("Second indice provided is not supported yet (user provided " << index2 << " )");
	}

	/*Build Triangle Gauss point*/
	for(int i=0;i<numgauss;i++){
		coords1[i]=0.5*(a1+a2) + 0.5*seg_coords[i]*(a2-a1);
		coords2[i]=0.5*(b1+b2) + 0.5*seg_coords[i]*(b2-b1);
		coords3[i]=0.5*(c1+c2) + 0.5*seg_coords[i]*(c2-c1);
		weights[i]=seg_weights[i];
	}

	/*Initialize static fields as undefined*/
	weight=UNDEF;
	coord1=UNDEF;
	coord2=UNDEF;
	coord3=UNDEF;

	/*clean up*/
	xDelete<double>(seg_coords);
	xDelete<double>(seg_weights);
}
/*}}}*/
GaussTria::GaussTria(IssmDouble area_coordinates[2][3],int order){/*{{{*/

	/*Intermediaties*/
	IssmPDouble *seg_coords  = NULL;
	IssmPDouble *seg_weights = NULL;

	/*Get Segment gauss points*/
	numgauss=order;
	GaussLegendreLinear(&seg_coords,&seg_weights,numgauss);

	/*Allocate GaussTria fields*/
	coords1=xNew<IssmDouble>(numgauss);
	coords2=xNew<IssmDouble>(numgauss);
	coords3=xNew<IssmDouble>(numgauss);
	weights=xNew<IssmDouble>(numgauss);

	/*Build Triangle Gauss point*/
	for(int i=0;i<numgauss;i++){
		coords1[i]=0.5*(area_coordinates[0][0]+area_coordinates[1][0]) + 0.5*seg_coords[i]*(area_coordinates[1][0]-area_coordinates[0][0]);
		coords2[i]=0.5*(area_coordinates[0][1]+area_coordinates[1][1]) + 0.5*seg_coords[i]*(area_coordinates[1][1]-area_coordinates[0][1]);
		coords3[i]=0.5*(area_coordinates[0][2]+area_coordinates[1][2]) + 0.5*seg_coords[i]*(area_coordinates[1][2]-area_coordinates[0][2]);
		weights[i]=seg_weights[i];
	}

	/*Initialize static fields as undefined*/
	weight=UNDEF;
	coord1=UNDEF;
	coord2=UNDEF;
	coord3=UNDEF;

	/*clean up*/
	xDelete<IssmPDouble>(seg_coords);
	xDelete<IssmPDouble>(seg_weights);
}
/*}}}*/
GaussTria::GaussTria(int index,IssmDouble r1,IssmDouble r2,bool mainlyfloating,int order){/*{{{*/

	/*
	 *  ^ 
	 *  |
	 * 1|\
	 *  |  \
	 *  |    \
	 *  |      \
	 *  |        \
	 *  |          \
	 *  |    +(x,y)  \
	 *  |              \
	 *  +---------------+-->
	 *  0               1
	 *
	 */
	int         ig;
	IssmDouble x,y;
	IssmDouble xy_list[3][2];

	if(mainlyfloating){
		/*Get gauss points*/
		GaussLegendreTria(&this->numgauss,&this->coords1,&this->coords2,&this->coords3,&this->weights,order);

		xy_list[0][0]=0;  xy_list[0][1]=0; 
		xy_list[1][0]=r1; xy_list[1][1]=0; 
		xy_list[2][0]=0;  xy_list[2][1]=r2; 

		for(ig=0;ig<this->numgauss;ig++){
			x = this->coords1[ig]*xy_list[0][0] + this->coords2[ig]*xy_list[1][0] + this->coords3[ig]*xy_list[2][0];
			y = this->coords1[ig]*xy_list[0][1] + this->coords2[ig]*xy_list[1][1] + this->coords3[ig]*xy_list[2][1];

			switch(index){
				case 0:
					this->coords1[ig] = 1.-x-y;
					this->coords2[ig] = x;
					this->coords3[ig] = y;
					break;
				case 1:
					this->coords1[ig] = y;
					this->coords2[ig] = 1.-x-y;
					this->coords3[ig] = x;
					break;
				case 2:
					this->coords1[ig] = x;
					this->coords2[ig] = y;
					this->coords3[ig] = 1.-x-y;
					break;
				default:
					_error_("index "<<index<<" not supported yet");
			}
			this->weights[ig] = this->weights[ig]*r1*r2;
		}
	}
	else{
		/*Double number of gauss points*/
		GaussTria *gauss1    = NULL;
		GaussTria *gauss2    = NULL;
		gauss1=new GaussTria(order);
		gauss2=new GaussTria(order);

		xy_list[0][0]=r1; xy_list[0][1]=0; 
		xy_list[1][0]=0;  xy_list[1][1]=1.; 
		xy_list[2][0]=0;  xy_list[2][1]=r2; 

			//gauss1->Echo();
		for(ig=0;ig<gauss1->numgauss;ig++){
			x = gauss1->coords1[ig]*xy_list[0][0] + gauss1->coords2[ig]*xy_list[1][0] + gauss1->coords3[ig]*xy_list[2][0];
			y = gauss1->coords1[ig]*xy_list[0][1] + gauss1->coords2[ig]*xy_list[1][1] + gauss1->coords3[ig]*xy_list[2][1];

			switch(index){
				case 0:
					gauss1->coords1[ig] = 1.-x-y;
					gauss1->coords2[ig] = x;
					gauss1->coords3[ig] = y;
					break;
				case 1:
					gauss1->coords1[ig] = y;
					gauss1->coords2[ig] = 1.-x-y;
					gauss1->coords3[ig] = x;
					break;
				case 2:
					gauss1->coords1[ig] = x;
					gauss1->coords2[ig] = y;
					gauss1->coords3[ig] = 1.-x-y;
					break;
				default:
					_error_("index "<<index<<" not supported yet");
			}
			gauss1->weights[ig] = gauss1->weights[ig]*r1*(1-r2);
		}
			//gauss1->Echo();
		xy_list[0][0]=r1; xy_list[0][1]=0; 
		xy_list[1][0]=1.; xy_list[1][1]=0; 
		xy_list[2][0]=0;  xy_list[2][1]=1.; 

			//gauss2->Echo();
		for(ig=0;ig<gauss2->numgauss;ig++){
			x = gauss2->coords1[ig]*xy_list[0][0] + gauss2->coords2[ig]*xy_list[1][0] + gauss2->coords3[ig]*xy_list[2][0];
			y = gauss2->coords1[ig]*xy_list[0][1] + gauss2->coords2[ig]*xy_list[1][1] + gauss2->coords3[ig]*xy_list[2][1];

			switch(index){
				case 0:
					gauss2->coords1[ig] = 1.-x-y;
					gauss2->coords2[ig] = x;
					gauss2->coords3[ig] = y;
					break;
				case 1:
					gauss2->coords1[ig] = y;
					gauss2->coords2[ig] = 1.-x-y;
					gauss2->coords3[ig] = x;
					break;
				case 2:
					gauss2->coords1[ig] = x;
					gauss2->coords2[ig] = y;
					gauss2->coords3[ig] = 1.-x-y;
					break;
				default:
					_error_("index "<<index<<" not supported yet");
			}
			gauss2->weights[ig] = gauss2->weights[ig]*(1-r1);
		}

		this->numgauss = gauss1->numgauss + gauss2->numgauss;
		this->coords1=xNew<IssmDouble>(this->numgauss);
		this->coords2=xNew<IssmDouble>(this->numgauss);
		this->coords3=xNew<IssmDouble>(this->numgauss);
		this->weights=xNew<IssmDouble>(this->numgauss);

		for(ig=0;ig<gauss1->numgauss;ig++){ // Add the first triangle gauss points
			this->coords1[ig]=gauss1->coords1[ig];
			this->coords2[ig]=gauss1->coords2[ig];
			this->coords3[ig]=gauss1->coords3[ig];
			this->weights[ig]=gauss1->weights[ig];
		}
		for(ig=0;ig<gauss2->numgauss;ig++){ // Add the second triangle gauss points
			this->coords1[gauss1->numgauss+ig]=gauss2->coords1[ig];
			this->coords2[gauss1->numgauss+ig]=gauss2->coords2[ig];
			this->coords3[gauss1->numgauss+ig]=gauss2->coords3[ig];
			this->weights[gauss1->numgauss+ig]=gauss2->weights[ig];
		}

		/*Delete gauss points*/
		delete gauss1;
		delete gauss2;
	}

	/*Initialize static fields as undefined*/
	weight=UNDEF;
	coord1=UNDEF;
	coord2=UNDEF;
	coord3=UNDEF;
}
/*}}}*/
GaussTria::~GaussTria(){/*{{{*/
	xDelete<IssmDouble>(weights);
	xDelete<IssmDouble>(coords3);
	xDelete<IssmDouble>(coords2);
	xDelete<IssmDouble>(coords1);

}
/*}}}*/

/*Methods*/
int GaussTria::begin(void){/*{{{*/

	/*Check that this has been initialized*/
	_assert_(numgauss>0);
	_assert_(weights);
	_assert_(coords1);
	_assert_(coords2);
	_assert_(coords3);

	/*return first gauss index*/
	return 0;
}
/*}}}*/
void GaussTria::Echo(void){/*{{{*/

	_printf_("GaussTria:\n");
	_printf_("   numgauss: " << numgauss << "\n");

	if (weights){
	 _printf_("   weights = ["); 
	 for(int i=0;i<numgauss;i++) _printf_(" " << weights[i] << "\n");
	 _printf_("]\n");
	}
	else _printf_("weights = NULL\n");
	if (coords1){
	 _printf_("   coords1 = ["); 
	 for(int i=0;i<numgauss;i++) _printf_(" " << coords1[i] << "\n");
	 _printf_("]\n");
	}
	else _printf_("coords1 = NULL\n");
	if (coords2){
	 _printf_("   coords2 = ["); 
	 for(int i=0;i<numgauss;i++) _printf_(" " << coords2[i] << "\n");
	 _printf_("]\n");
	}
	else _printf_("coords2 = NULL\n");
	if (coords3){
	 _printf_("   coords3 = ["); 
	 for(int i=0;i<numgauss;i++) _printf_(" " << coords3[i] << "\n");
	 _printf_("]\n");
	}
	else _printf_("coords3 = NULL\n");

	_printf_("   weight = " << weight << "\n");
	_printf_("   coord1 = " << coord1 << "\n");
	_printf_("   coord2 = " << coord2 << "\n");
	_printf_("   coord3 = " << coord3 << "\n");

}
/*}}}*/
int GaussTria::end(void){/*{{{*/

	/*Check that this has been initialized*/
	_assert_(numgauss>0);
	_assert_(weights);
	_assert_(coords1);
	_assert_(coords2);
	_assert_(coords3);

	/*return last gauss index +1*/
	return numgauss;
}
/*}}}*/
int GaussTria::Enum(void){/*{{{*/
	return GaussTriaEnum;
}
/*}}}*/
void GaussTria::GaussEdgeCenter(int index1,int index2){/*{{{*/

	int     index3;

	/*Reverse index1 and 2 if necessary*/
	if (index1>index2){
		index3=index1; index1=index2; index2=index3;
	}

	/*update static arrays*/
	if (index1==0 && index2==1){
		coord1=0.5;
		coord2=0.5;
		coord3=0.0;
	}
	else if (index1==0 && index2==2){
		coord1=0.5;
		coord2=0.0;
		coord3=0.5;
	}
	else if (index1==1 && index2==2){
		coord1=0.0;
		coord2=0.5;
		coord3=0.5;
	}
	else
	 _error_("The 2 indices provided are not supported yet (user provided " << index1 << " and " << index2 << ")");

}
/*}}}*/
void GaussTria::GaussFromCoords(IssmDouble x,IssmDouble y,IssmDouble* xyz_list){/*{{{*/

	/*Intermediaries*/
	IssmDouble    area = 0;
	IssmDouble    x1,y1,x2,y2,x3,y3;

	/*in debugging mode: check that the default constructor has been called*/
	_assert_(numgauss==-1);

	x1=*(xyz_list+3*0+0); y1=*(xyz_list+3*0+1);
	x2=*(xyz_list+3*1+0); y2=*(xyz_list+3*1+1);
	x3=*(xyz_list+3*2+0); y3=*(xyz_list+3*2+1);

	area=(x2*y3 - y2*x3 + x1*y2 - y1*x2 + x3*y1 - y3*x1)/2;

	/*Get first area coordinate = det(x-x3  x2-x3 ; y-y3   y2-y3)/area*/
	coord1=((x-x3)*(y2-y3)-(x2-x3)*(y-y3))/area;

	/*Get second area coordinate = det(x1-x3  x-x3 ; y1-y3   y-y3)/area*/
	coord2=((x1-x3)*(y-y3)-(x-x3)*(y1-y3))/area;

	/*Get third  area coordinate 1-area1-area2: */
	coord3=1-coord1-coord2;

}
/*}}}*/
void GaussTria::GaussPoint(int ig){/*{{{*/

	/*Check input in debugging mode*/
	 _assert_(ig>=0 && ig< numgauss);

	 /*update static arrays*/
	 weight=weights[ig];
	 coord1=coords1[ig];
	 coord2=coords2[ig];
	 coord3=coords3[ig];

}
/*}}}*/
void GaussTria::GaussNode(int finiteelement,int iv){/*{{{*/

	/*in debugging mode: check that the default constructor has been called*/
	_assert_(numgauss==-1);

	/*update static arrays*/
	switch(finiteelement){
		case P0Enum:
			switch(iv){
				case 0: coord1=1./3.; coord2=1./3.; coord3=1./3.; break;
				default: _error_("node index should be 0");
			}
			break;
		case P1Enum: case P1DGEnum:
			switch(iv){
				case 0: coord1=1.; coord2=0.; coord3=0.; break;
				case 1: coord1=0.; coord2=1.; coord3=0.; break;
				case 2: coord1=0.; coord2=0.; coord3=1.; break;
				default: _error_("node index should be in [0 2]");
			}
			break;
		case P1bubbleEnum: case P1bubblecondensedEnum:
			switch(iv){
				case 0: coord1=1.;    coord2=0.;    coord3=0.;    break;
				case 1: coord1=0.;    coord2=1.;    coord3=0.;    break;
				case 2: coord1=0.;    coord2=0.;    coord3=1.;    break;
				case 3: coord1=1./3.; coord2=1./3.; coord3=1./3.; break;
				default: _error_("node index should be in [0 3]");
			}
			break;
		case P2Enum:
			switch(iv){
				case 0: coord1=1.; coord2=0.; coord3=0.; break;
				case 1: coord1=0.; coord2=1.; coord3=0.; break;
				case 2: coord1=0.; coord2=0.; coord3=1.; break;
				case 3: coord1=0.; coord2=.5; coord3=.5; break;
				case 4: coord1=.5; coord2=0.; coord3=.5; break;
				case 5: coord1=.5; coord2=.5; coord3=0.; break;
				default: _error_("node index should be in [0 5]");
			}
			break;
		case P2bubbleEnum: case P2bubblecondensedEnum:
			switch(iv){
				case 0: coord1=1.; coord2=0.; coord3=0.; break;
				case 1: coord1=0.; coord2=1.; coord3=0.; break;
				case 2: coord1=0.; coord2=0.; coord3=1.; break;
				case 3: coord1=0.; coord2=.5; coord3=.5; break;
				case 4: coord1=.5; coord2=0.; coord3=.5; break;
				case 5: coord1=.5; coord2=.5; coord3=0.; break;
				case 6: coord1=1./3.; coord2=1./3.; coord3=1./3.; break;
				default: _error_("node index should be in [0 6]");
			}
			break;
		default: _error_("Finite element "<<EnumToStringx(finiteelement)<<" not supported");
	}

}
/*}}}*/
void GaussTria::GaussVertex(int iv){/*{{{*/

	/*in debugging mode: check that the default constructor has been called*/
	_assert_(numgauss==-1);

	/*update static arrays*/
	switch(iv){
		case 0: coord1=1.; coord2=0.; coord3=0.; break;
		case 1: coord1=0.; coord2=1.; coord3=0.; break;
		case 2: coord1=0.; coord2=0.; coord3=1.; break;
		default: _error_("vertex index should be in [0 2]");
	}

}
/*}}}*/
void GaussTria::SynchronizeGaussBase(Gauss* gauss){/*{{{*/

	_error_("not supported");
}
/*}}}*/
