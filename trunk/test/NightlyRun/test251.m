%Test Name: SquareShelfTranForceNeg2dDakotaLocalLinearPart
md=triangle(model(),'../Exp/Square.exp',180000.);
md=setmask(md,'all','');
md=parameterize(md,'../Par/SquareShelf.par');
md=setflowequation(md,'SSA','all');
md.cluster=generic('name',oshostname(),'np',3);

md.timestepping.time_step=1;
md.settings.output_frequency=1;
md.timestepping.final_time=4;

smb = ones(md.mesh.numberofvertices,1)*3.6;
smb=[ smb smb*-1 ];

md.smb.mass_balance= smb;
md.smb.mass_balance(end+1,:)=[1.5 3];
md.transient.isthermal=0;
%Dakota options

%dakota version
version=IssmConfig('_DAKOTA_VERSION_'); version=version(1:3); version=str2num(version);

%partitioning
md.qmu.numberofpartitions=md.mesh.numberofvertices;
md=partitioner(md,'package','linear');
md.qmu.partition=md.qmu.partition-1;

%variables
md.qmu.variables.surface_mass_balance=normal_uncertain('scaled_SmbMassBalance',1,100);

%responses
md.qmu.responses.MaxVel=response_function('MaxVel',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.IceVolume=response_function('IceVolume',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.MassFlux1=response_function('indexed_MassFlux_1',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.MassFlux2=response_function('indexed_MassFlux_2',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.MassFlux3=response_function('indexed_MassFlux_3',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.MassFlux4=response_function('indexed_MassFlux_4',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.MassFlux5=response_function('indexed_MassFlux_5',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);
md.qmu.responses.massFlux6=response_function('indexed_MassFlux_6',[],[0.0001 0.001 0.01 0.25 0.5 0.75 0.99 0.999 0.9999]);

%mass flux profiles
md.qmu.mass_flux_profiles={'../Exp/MassFlux1.exp','../Exp/MassFlux2.exp','../Exp/MassFlux3.exp','../Exp/MassFlux4.exp','../Exp/MassFlux5.exp','../Exp/MassFlux6.exp'};
md.qmu.mass_flux_profile_directory=pwd;

%method
md.qmu.method     =dakota_method('nond_l');

%parameters
md.qmu.params.direct=true;
md.qmu.params.analysis_components='';
md.qmu.params.interval_type='forward';
md.qmu.params.fd_gradient_step_size='0.1';
md.qmu.isdakota=1;

if version>=6,
	md.qmu.params.analysis_driver='matlab';
	md.qmu.params.evaluation_scheduling='master';
	md.qmu.params.processors_per_evaluation=2;
else
	md.qmu.params.analysis_driver='stressbalance';
	md.qmu.params.evaluation_concurrency=1;
end


md.stressbalance.reltol=10^-5; %tighten for qmu analyses
md.transient.requested_outputs={'IceVolume'};

%solve
md=solve(md,'Transient','overwrite','y');
md.qmu.results=md.results.dakota;

%Fields and tolerances to track changes
md.results.dakota.moments=[];
for i=1:8,
	md.results.dakota.moments=[md.results.dakota.moments md.results.dakota.dresp_out(i).mean];
end
for i=1:8,
	md.results.dakota.moments=[md.results.dakota.moments md.results.dakota.dresp_out(i).stddev];
end
field_names     ={'moments'};
field_tolerances={1e-11};
field_values={...
         md.results.dakota.moments,...
	};