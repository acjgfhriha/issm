%LEVELSET class definition
%
%   Usage:
%      levelset=levelset();

classdef levelset
	properties (SetAccess=public) 
		stabilization		= 0;
		spclevelset			= NaN;
		reinit_frequency	= 5;
		calving_max       = 0.;
	end
	methods
		function self = levelset(varargin) % {{{
			switch nargin
				case 0
					self=setdefaultparameters(self);
				case 1
					inputstruct=varargin{1};
					list1 = properties('levelset');
					list2 = fieldnames(inputstruct);
					for i=1:length(list1)
						fieldname = list1{i};
						if ismember(fieldname,list2),
							self.(fieldname) = inputstruct.(fieldname);
						end
					end
				otherwise
					error('constructor not supported');
			end
		end % }}}
		function self = extrude(self,md) % {{{

			self.spclevelset=project3d(md,'vector',self.spclevelset,'type','node');
		end % }}}
		function self = setdefaultparameters(self) % {{{

			%stabilization = 2 by default
			self.stabilization    = 2;
			self.reinit_frequency = 5;
			self.calving_max      = 3000.;

		end % }}}
		function md = checkconsistency(self,md,solution,analyses) % {{{
			%Early return
			if (~strcmp(solution,'TransientSolution') | md.transient.ismovingfront==0), return; end

			md = checkfield(md,'fieldname','levelset.spclevelset','Inf',1,'timeseries',1);
			md = checkfield(md,'fieldname','levelset.stabilization','values',[0 1 2]);
			md = checkfield(md,'fieldname','levelset.calving_max','numel',1,'NaN',1,'Inf',1,'>',0);
		end % }}}
		function disp(self) % {{{
			disp(sprintf('   Level-set parameters:'));
			fielddisplay(self,'stabilization','0: no, 1: artificial_diffusivity, 2: streamline upwinding');
			fielddisplay(self,'spclevelset','Levelset constraints (NaN means no constraint)');
			fielddisplay(self,'reinit_frequency','Amount of time steps after which the levelset function in re-initialized');
			fielddisplay(self,'calving_max','maximum allowed calving rate (m/a)');
		end % }}}
		function marshall(self,prefix,md,fid) % {{{

			yts=md.constants.yts;

			WriteData(fid,prefix,'object',self,'fieldname','stabilization','format','Integer');
			WriteData(fid,prefix,'object',self,'fieldname','spclevelset','format','DoubleMat','mattype',1,'timeserieslength',md.mesh.numberofvertices+1,'yts',md.constants.yts);
			WriteData(fid,prefix,'object',self,'fieldname','reinit_frequency','format','Integer');
			WriteData(fid,prefix,'object',self,'fieldname','calving_max','format','Double','scale',1./yts);
		end % }}}
		function savemodeljs(self,fid,modelname) % {{{
		
			writejsdouble(fid,[modelname '.levelset.stabilization'],self.stabilization);
			writejs1Darray(fid,[modelname '.levelset.spclevelset'],self.spclevelset);
			writejs1Darray(fid,[modelname '.levelset.reinit_frequency'],self.reinit_frequency);
			writejsdouble(fid,[modelname '.levelset.calving_max'],self.calving_max);

		end % }}}
	end
end

