/*Original code from Frederic Hecht <hecht@ann.jussieu.fr> (BAMG v1.01, BamgQuadtree.h)*/
#ifndef _BAMGQUADTREE_H
#define _BAMGQUADTREE_H

#include "./include.h"
#include "../datastructures/datastructures.h"
class BamgVertex;

namespace bamg {
	class BamgQuadtree{

		private:

			/*A quadtree box contains a maximum of 4 vertices. 4 other quadtree boxes are
			 * created if a fifth vertex is added to the same box. A Quadtree box is therefore
			 * composed of EITHER:
			 * - up to 4 vertices
			 * - 4 "sub" quadtree boxes*/
			class BamgQuadtreeBox: public Object{ 
				public:
					int              nbitems;
					BamgQuadtreeBox *box[4];
					BamgVertex      *v[4];
					/*Object functions*/
					void    Echo()       {_error_("not implemented yet"); };
					void    DeepEcho()   {_error_("not implemented yet"); };
					int     Id()         {_error_("not implemented yet"); };
					int     ObjectEnum() {_error_("not implemented yet"); };
					Object *copy()       {_error_("not implemented yet"); };
					void Marshall(char** pmarshalled_data,int* pmarshalled_data_size, int marshall_direction){ _error_("not implemented yet!"); };
			};

			/*BamgQuadtree private Fields*/
			DataSet* boxcontainer;

		public:

			/*BamgQuadtree public Fields*/
			BamgQuadtreeBox *root;            // main box
			long             NbQuadtreeBox;   // total number of boxes
			long             NbVertices;      // number of points

			BamgQuadtree();
			BamgQuadtree(Mesh *t,long nbv=-1);
			~BamgQuadtree();

			void             Add(BamgVertex &w);
			int              BoxNumber(int i,int j,int l);
			bool             Intersection(int a,int b,int x,int y);
			BamgVertex      *NearestVertex(int i,int j);
			BamgQuadtreeBox *NewBamgQuadtreeBox(void);
			int              Norm(int xi1,int yi1,int xi2,int yi2);
			void             SubBoxCoords(int* pi,int*pj,int boxcoord,int length);
			BamgVertex      *TooClose(BamgVertex*,double,int,int);
	};
}
#endif
