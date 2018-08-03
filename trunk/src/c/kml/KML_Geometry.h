/*! \file KML_Geometry.h 
 *  \brief: header file for kml_geometry abstract object
 */

#ifndef _KML_GEOMETRY_H_
#define _KML_GEOMETRY_H_

/*Headers:*/
/*{{{*/
#include "../shared/shared.h"
#include "./KML_Object.h"
/*}}}*/

class KML_Geometry: public KML_Object {

	public:

		/*KML_Geometry constructors, destructors {{{*/
		KML_Geometry();
		~KML_Geometry();
		/*}}}*/
		/*Object virtual functions definitions:{{{*/
		void  Echo();
		void  DeepEcho();
		void  DeepEcho(const char* indent);
		void  Write(FILE* fid,const char* indent);
		void  Read(FILE* fid,char* kstr);
		int   Id(){_error_("Not implemented yet.");};
		int   ObjectEnum(){_error_("Not implemented yet.");};
		Object* copy(){_error_("Not implemented yet.");};
		void Marshall(char** pmarshalled_data,int* pmarshalled_data_size, int marshall_direction){ _error_("not implemented yet!");};
		/*}}}*/

};
#endif  /* _KML_GEOMETRY_H */
