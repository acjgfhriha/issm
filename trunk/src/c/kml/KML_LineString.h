/*! \file KML_LineString.h 
 *  \brief: header file for kml_linestring object
 */

#ifndef _KML_LINESTRING_H_
#define _KML_LINESTRING_H_

#define KML_LINESTRING_ALTMODE_LENGTH    18

/*Headers:*/
/*{{{*/
#include "../shared/shared.h"
#include "./KML_Geometry.h"
/*}}}*/

class KML_LineString: public KML_Geometry {

	public:

		bool    extrude;
		bool    tessellate;
		char    altmode[KML_LINESTRING_ALTMODE_LENGTH+1];
		int     ncoord;
		double *coords;

		/*KML_LineString constructors, destructors {{{*/
		KML_LineString();
		~KML_LineString();
		/*}}}*/
		/*Object virtual functions definitions:{{{*/
		void  Echo();
		void  DeepEcho();
		void  DeepEcho(const char* indent);
		void  Write(FILE* fid,const char* indent);
		void  Read(FILE* fid,char* kstr);
		void  WriteExp(FILE* fid,const char* nstr,int sgn,double cm,double sp);
		int   Id(){_error_("Not implemented yet.");};
		int   ObjectEnum(){_error_("Not implemented yet.");};
		Object* copy(){_error_("Not implemented yet.");};
		void Marshall(char** pmarshalled_data,int* pmarshalled_data_size, int marshall_direction){ _error_("not implemented yet!");};
		/*}}}*/

};
#endif  /* _KML_LINESTRING_H */
