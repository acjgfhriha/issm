function mdOut = remesh(md,parfile)
%Set the new mesh (refined) into the model md

NewModel = model;

% geometry
NewModel.mesh				= mesh2d();
NewModel.mesh.x			= md.results.TransientSolution(end).MeshX;
NewModel.mesh.y			= md.results.TransientSolution(end).MeshY;
NewModel.mesh.elements	= md.results.TransientSolution(end).MeshElements;

% build segments. CONVEX HULL: IT JUST WORKS FOR REGULAR MESHES, WITHOUT "BAYS"
disp('Building segments: searching vertices by convex hull...');
k					= convhull(NewModel.mesh.x,NewModel.mesh.y);
nsegments		= length(k)-1;
nelements		= size(NewModel.mesh.elements,1);
segments			= zeros(nsegments,3);
segments(:,1)	= k(1:nsegments);
segments(:,2)	= k(2:(nsegments+1));
disp('Building segments: searching boundary elements...');
for s=1:nsegments,
	for e=1:nelements,
		if any(NewModel.mesh.elements(e,:)==segments(s,1)) && any(NewModel.mesh.elements(e,:)==segments(s,2))
			segments(s,3)=e;
			break;
		end
	end

	if segments(s,3)==0,
		error('Element not found!');
	end
end

NewModel.mesh.segments  = segments;
%NewModel.mesh.segmentmarkers = segmentmarkers;

% connectivity
% Fill in rest of fields:
NewModel.mesh.numberofelements = size(NewModel.mesh.elements,1);
NewModel.mesh.numberofvertices = length(NewModel.mesh.x);
NewModel.mesh.vertexonboundary = zeros(NewModel.mesh.numberofvertices,1);
NewModel.mesh.vertexonboundary(NewModel.mesh.segments(:,1:2)) = 1;

% Now, build the connectivity tables for this mesh.
NewModel.mesh.vertexconnectivity = NodeConnectivity(NewModel.mesh.elements,NewModel.mesh.numberofvertices);
NewModel.mesh.elementconnectivity = ElementConnectivity(NewModel.mesh.elements,NewModel.mesh.vertexconnectivity);

% Building a bed topography and others parameters
NewModel = setmask(NewModel,'','');
NewModel = parameterize(NewModel, parfile);

% Setting initialization
NewModel.initialization.vx				= md.results.TransientSolution(end).Vx;
NewModel.initialization.vy				= md.results.TransientSolution(end).Vy;
NewModel.initialization.vz				= zeros(md.mesh.numberofvertices,1);
NewModel.initialization.vel			= md.results.TransientSolution(end).Vel;
NewModel.initialization.pressure    = md.results.TransientSolution(end).Pressure;
NewModel.geometry.surface				= md.results.TransientSolution(end).Surface;
NewModel.geometry.base					= md.results.TransientSolution(end).Base;
%NewModel.geometry.bed					= md.geometry.bed; %use from parameterize
NewModel.geometry.thickness			= md.results.TransientSolution(end).Thickness;
NewModel.mask.groundedice_levelset  = md.results.TransientSolution(end).MaskGroundediceLevelset;
    
%copy other data
NewModel.miscellaneous          = md.miscellaneous;
NewModel.timestepping           = md.timestepping;
NewModel.settings               = md.settings;
NewModel.stressbalance.maxiter  = md.stressbalance.maxiter;
NewModel.stressbalance.abstol   = md.stressbalance.abstol;
NewModel.stressbalance.restol   = md.stressbalance.restol;
NewModel.verbose                = md.verbose;
NewModel.cluster                = md.cluster;
NewModel.transient              = md.transient;

mdOut = NewModel;

end
