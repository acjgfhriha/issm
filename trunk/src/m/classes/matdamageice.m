%MATDAMAGEICE class definition
%
%   Usage:
%      matdamageice=matdamageice();

classdef matdamageice
	properties (SetAccess=public) 
		rho_ice                    = 0.;
		rho_water                  = 0.;
		rho_freshwater             = 0.;
		mu_water                   = 0.;
		heatcapacity               = 0.;
		latentheat                 = 0.;
		thermalconductivity        = 0.;
		temperateiceconductivity   = 0.;
		meltingpoint               = 0.;
		beta                       = 0.;
		mixed_layer_capacity       = 0.;
		thermal_exchange_velocity  = 0.;
		rheology_B   = NaN;
		rheology_n   = NaN;
		rheology_law = '';

		%giaivins: 
		lithosphere_shear_modulus  = 0.;
		lithosphere_density        = 0.;
		mantle_shear_modulus       = 0.;
		mantle_density             = 0.;

		%slr
		earth_density              = 0;

	end
	methods
		function self = extrude(self,md) % {{{
			self.rheology_B=project3d(md,'vector',self.rheology_B,'type','node');
			self.rheology_n=project3d(md,'vector',self.rheology_n,'type','element');
		end % }}}
		function self = matdamageice(varargin) % {{{
			switch nargin
				case 0
					self=setdefaultparameters(self);
				case 1
					inputstruct=varargin{1};
					list1 = properties('matdamageice');
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
		function self = setdefaultparameters(self) % {{{

			%ice density (kg/m^3)
			self.rho_ice=917.;

			%ocean water density (kg/m^3)
			self.rho_water=1023.;

			%fresh water density (kg/m^3)
			self.rho_freshwater=1000.;

			%water viscosity (N.s/m^2)
			self.mu_water=0.001787;  

			%ice heat capacity cp (J/kg/K)
			self.heatcapacity=2093.;

			%ice latent heat of fusion L (J/kg)
			self.latentheat=3.34*10^5;

			%ice thermal conductivity (W/m/K)
			self.thermalconductivity=2.4;
			
			%wet ice thermal conductivity (W/m/K)
			self.temperateiceconductivity=.24;

			%the melting point of ice at 1 atmosphere of pressure in K
			self.meltingpoint=273.15;

			%rate of change of melting point with pressure (K/Pa)
			self.beta=9.8*10^-8;

			%mixed layer (ice-water interface) heat capacity (J/kg/K)
			self.mixed_layer_capacity=3974.;

			%thermal exchange velocity (ice-water interface) (m/s)
			self.thermal_exchange_velocity=1.00*10^-4;

			%Rheology law: what is the temperature dependence of B with T
			%available: none, paterson and arrhenius
			self.rheology_law='Paterson';

			% GIA:
			self.lithosphere_shear_modulus  = 6.7*10^10;  % (Pa)
			self.lithosphere_density        = 3.32;       % (g/cm^-3)
			self.mantle_shear_modulus       = 1.45*10^11; % (Pa)
			self.mantle_density             = 3.34;       % (g/cm^-3)

			%SLR
			self.earth_density= 5512;  % average density of the Earth, (kg/m^3)

		end % }}}
		function md = checkconsistency(self,md,solution,analyses) % {{{
			md = checkfield(md,'fieldname','materials.rho_ice','>',0);
			md = checkfield(md,'fieldname','materials.rho_water','>',0);
			md = checkfield(md,'fieldname','materials.rho_freshwater','>',0);
			md = checkfield(md,'fieldname','materials.mu_water','>',0);
			md = checkfield(md,'fieldname','materials.rheology_B','>',0,'size',[md.mesh.numberofvertices 1]);
			md = checkfield(md,'fieldname','materials.rheology_n','>',0,'size',[md.mesh.numberofelements 1]);
			md = checkfield(md,'fieldname','materials.rheology_law','values',{'None' 'BuddJacka' 'Cuffey' 'CuffeyTemperate' 'Paterson' 'Arrhenius' 'LliboutryDuval'});

			if ismember('GiaAnalysis',analyses),
				md = checkfield(md,'fieldname','materials.lithosphere_shear_modulus','>',0,'numel',1);
				md = checkfield(md,'fieldname','materials.lithosphere_density','>',0,'numel',1);
				md = checkfield(md,'fieldname','materials.mantle_shear_modulus','>',0,'numel',1);
				md = checkfield(md,'fieldname','materials.mantle_density','>',0,'numel',1);
			end
			if ismember('SealevelriseAnalysis',analyses),
				md = checkfield(md,'fieldname','materials.earth_density','>',0,'numel',1);
			end


		end % }}}
		function disp(self) % {{{
			disp(sprintf('   Materials:'));

			fielddisplay(self,'rho_ice','ice density [kg/m^3]');
			fielddisplay(self,'rho_water','ocean water density [kg/m^3]');
			fielddisplay(self,'rho_freshwater','fresh water density [kg/m^3]');
			fielddisplay(self,'mu_water','water viscosity [N s/m^2]');
			fielddisplay(self,'heatcapacity','heat capacity [J/kg/K]');
			fielddisplay(self,'thermalconductivity',['ice thermal conductivity [W/m/K]']);
			fielddisplay(self,'temperateiceconductivity','temperate ice thermal conductivity [W/m/K]');
			fielddisplay(self,'meltingpoint','melting point of ice at 1atm in K');
			fielddisplay(self,'latentheat','latent heat of fusion [J/kg]');
			fielddisplay(self,'beta','rate of change of melting point with pressure [K/Pa]');
			fielddisplay(self,'mixed_layer_capacity','mixed layer capacity [W/kg/K]');
			fielddisplay(self,'thermal_exchange_velocity','thermal exchange velocity [m/s]');
			fielddisplay(self,'rheology_B','flow law parameter [Pa/s^(1/n)]');
			fielddisplay(self,'rheology_n','Glen''s flow law exponent');
			fielddisplay(self,'rheology_law',['law for the temperature dependance of the rheology: ''None'', ''BuddJacka'', ''Cuffey'', ''CuffeyTemperate'', ''Paterson'', ''Arrhenius'' or ''LliboutryDuval''']);
			fielddisplay(self,'lithosphere_shear_modulus','Lithosphere shear modulus [Pa]');
			fielddisplay(self,'lithosphere_density','Lithosphere density [g/cm^-3]');
			fielddisplay(self,'mantle_shear_modulus','Mantle shear modulus [Pa]');
			fielddisplay(self,'mantle_density','Mantle density [g/cm^-3]');
			fielddisplay(self,'earth_density','Mantle density [kg/m^-3]');
		end % }}}
		function marshall(self,prefix,md,fid) % {{{
			WriteData(fid,prefix,'name','md.materials.type','data',1,'format','Integer');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','rho_ice','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','rho_water','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','rho_freshwater','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','mu_water','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','heatcapacity','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','latentheat','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','thermalconductivity','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','temperateiceconductivity','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','meltingpoint','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','beta','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','mixed_layer_capacity','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','thermal_exchange_velocity','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','rheology_B','format','DoubleMat','mattype',1);
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','rheology_n','format','DoubleMat','mattype',2);
			WriteData(fid,prefix,'data',self.rheology_law,'name','md.materials.rheology_law','format','String');

			WriteData(fid,prefix,'object',self,'class','materials','fieldname','lithosphere_shear_modulus','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','lithosphere_density','format','Double','scale',10^3);
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','mantle_shear_modulus','format','Double');
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','mantle_density','format','Double','scale',10^3);
			WriteData(fid,prefix,'object',self,'class','materials','fieldname','earth_density','format','Double');

		end % }}}
	end
end