/* \file classes.h
 * \brief: prototype header for all classes used in ISSM.
 */

#ifndef _ALL_CLASSES_H_
#define _ALL_CLASSES_H_

/*Objects: */
#include "./Contour.h"
#include "./Vertices.h"
#include "./Vertex.h"
#include "./Nodes.h"
#include "./Contours.h"
#include "./Node.h"
#include "./Profiler.h"
#include "./DependentObject.h"
#include "./Segment.h"
#include "./Massfluxatgate.h"
#include "./Misfit.h"
#include "./Nodalvalue.h"
#include "./Masscon.h"
#include "./Massconaxpby.h"

/*Constraints: */
#include "./Constraints/Constraints.h"
#include "./Constraints/Constraint.h"
#include "./Constraints/SpcStatic.h"
#include "./Constraints/SpcTransient.h"
#include "./Constraints/SpcDynamic.h"

/*Loads: */
#include "./Loads/Loads.h"
#include "./Loads/Load.h"
#include "./Loads/Friction.h"
#include "./Loads/Numericalflux.h"
#include "./Loads/Neumannflux.h"
#include "./Loads/Riftfront.h"
#include "./Loads/Penpair.h"
#include "./Loads/Pengrid.h"
#include "./Loads/Moulin.h"

/*Elements: */
#include "./Elements/Elements.h"
#include "./Elements/Element.h"
#include "./Elements/Penta.h"
#include "./Elements/PentaRef.h"
#include "./Elements/Seg.h"
#include "./Elements/SegRef.h"
#include "./Elements/Tria.h"
#include "./Elements/TriaRef.h"
#include "./Elements/Tetra.h"
#include "./Elements/TetraRef.h"
#include "./Elements/ElementHook.h"

/*Option parsing objects: */
#include "./Options/Option.h"
#include "./Options/Options.h"
#include "./Options/GenericOption.h"
#include "./Options/OptionUtilities.h"

/*Inputs: */
#include "./Inputs/Inputs.h"
#include "./Inputs/Input.h"
#include "./Inputs/BoolInput.h"
#include "./Inputs/DoubleInput.h"
#include "./Inputs/DoubleArrayInput.h"
#include "./Inputs/IntInput.h"
#include "./Inputs/TetraInput.h"
#include "./Inputs/PentaInput.h"
#include "./Inputs/TriaInput.h"
#include "./Inputs/SegInput.h"
#include "./Inputs/ControlInput.h"
#include "./Inputs/DatasetInput.h"
#include "./Inputs/TransientInput.h"

/*ExternalResults: */
#include "./ExternalResults/Results.h"
#include "./ExternalResults/ExternalResult.h"
#include "./ExternalResults/GenericExternalResult.h"

/*Materials: */
#include "./Materials/Materials.h"
#include "./Materials/Material.h"
#include "./Materials/Matice.h"
#include "./Materials/Matestar.h"
#include "./Materials/Matpar.h"

/*Params: */
#include "./Params/GenericParam.h"
#include "./Params/BoolParam.h"
#include "./Params/DoubleMatParam.h"
#include "./Params/DoubleTransientMatParam.h"
#include "./Params/DoubleMatArrayParam.h"
#include "./Params/DoubleParam.h"
#include "./Params/DoubleVecParam.h"
#include "./Params/IntParam.h"
#include "./Params/IntVecParam.h"
#include "./Params/IntMatParam.h"
#include "./Params/FileParam.h"
#include "./Params/Parameters.h"
#include "./Params/Param.h"
#include "./Params/MatrixParam.h"
#include "./Params/VectorParam.h"
#include "./Params/StringArrayParam.h"
#include "./Params/StringParam.h"
#include "./Params/TransientParam.h"
#include "./Params/DataSetParam.h"

/*matrix: */
#include "./matrix/matrixobjects.h"

/*gauss: */
#include "./gauss/gaussobjects.h"

/*kriging: */
#include "./kriging/krigingobjects.h"

/*dakota:*/
#include "./Dakota/IssmDirectApplicInterface.h"
#include "./Dakota/IssmParallelDirectApplicInterface.h"

/*diverse: */
#include "./Hook.h"
#include "./DofIndexing.h"
#include "./IoModel.h"
#include "./Update.h"
#include "./FemModel.h"
#include "./GiaDeflectionCoreArgs.h"
#include "./RiftStruct.h"

#endif
