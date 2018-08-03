function [h,I]=dem(x,y,z,varargin)
%DEM Shaded relief image plot
%	DEM(X,Y,Z) plots the Digital Elevation Model defined by X and Y 
%	coordinate vectors and elevation matrix Z, as a lighted image using
%	specific "landcolor" and "seacolor" colormaps. DEM uses IMAGESC 
%	function which is much faster than SURFL when dealing with large 
%	high-resolution DEM.
%
%	DEM(X,Y,Z,OPT) specifies options with OPT = [A,C,SCUT,ZMIN,ZMAX,ZCUT],
%	where sorted optional scalars are:
%	  A = azimuth light (in degrees relative to North). Default is A = -45
%	      for a natural northwestern illumination.
%	  C = controls contrast, as the exponent of the gradient value. Default
%	      is C = 1 for linear contrast; use C = 0 to remove lighting, 
%	      C = 0.5 for moderate lighting, C = 2 or more for strong contrast.
%	  SCUT = controls lighting scale saturation with a median-style filter
%	      in % of elements. Default is SCUT = 0.2 (0.2% maximum gradient 
%	      values is ignored). Use SCUT = 0 for full scale gradient.
%	  ZMIN,ZMAX = fixes min and max elevation values for colormap. Use NaN
%	      to keep real min and/or max data values.
%	  ZCUT = median-style filter to cut extremes values (in % of elements).
%	      Default is ZCUT = 0.5 to ignore the 0.5% of most min/max 
%	      elevation values. Use ZCUT = 0 for full scale.
%	Use OPT=[] to keep default values and define following arguments.
%
%	DEM(...,CMAP) uses CMAP colormap instead of default (landcolor, if 
%	exists or jet). Note that defining CMAP disables the default SEACOLOR
%	colormap attribution for Z<=0 elevations.
%
%	DEM(...,NOVALUE) defines the values that will be replaced by NaN. This 
%	might be mandatory for DEM that use a value like -99999 or -32768 if 
%	you don't want a flat image...
%
%	DEM(...,SEACOLOR) sets the colormap used for zero and negative values.
%	Default is seacolor (if exists) or single color [0.7,0.9,1] (a light 
%	cyan) to simulate sea color. Use [] to apply colormap CMAP on the full
%	elevation scale.
%
%	DEM(...,'interp') interpolates linearly NaN values (fills the gaps).
%
%	DEM(...,'lake') detects automaticaly flat areas different from sea 
%	level (non-zero elevations) and draws them as lake surfaces.
%
%	DEM(...,'dec') plots classic basemap-style axis, considering 
%	coordinates as cartesian (decimal).
%
%	DEM(...,'dms') plots geographic basemap-style axis in deg/min/sec,
%	considering coordinates X as longitude and Y as latitude. Axis aspect 
%	ratio will be adjusted to approximatively preserve distances (this is  
%	not a real projection!).
%
%	DEM(...,'scale') adds a legend to the right of graph, with elevation 
%	scale (colormap) and a distance scale if 'dms' option is used.
%
%	[H,I]=DEM(...) returns graphic handle H and illuminated image as I, an
%	MxNx3 matrix (if Z is MxN).
%
%	Informations:
%	 - For optimization purpose, DEM will automatically decimate data to
%	   limit to a total of 1500x1500 pixels images. To avoid it, use option
%	   DEM(...,'nodecim') or DEM(...,'decim',N) where N is an integer, but 
%	   be aware that large grids may require computer ressources and induce  
%	   disk swap or memory errors.
%	 - Colormaps are Mx3 RGB matrix so it is easy to modify saturation 
%	   (CMAP.^N), set darker (CMAP/N), lighter ((N - 1 + CMAP)/N), inverse
%	    it (flipud(CMAP)), etc...
%	 - To get free worldwide topographic data (SRTM), see READHGT function.
%
%	Author: Fran�ois Beauducel <beauducel@ipgp.fr>
%	Created: 2007-05-17
%	Updated: 2013-01-05

%	Copyright (c) 2013, Fran�ois Beauducel, covered by BSD License.
%	All rights reserved.
%
%	Redistribution and use in source and binary forms, with or without 
%	modification, are permitted provided that the following conditions are 
%	met:
%
%	   * Redistributions of source code must retain the above copyright 
%	     notice, this list of conditions and the following disclaimer.
%	   * Redistributions in binary form must reproduce the above copyright 
%	     notice, this list of conditions and the following disclaimer in 
%	     the documentation and/or other materials provided with the distribution
%	                           
%	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
%	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
%	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
%	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
%	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
%	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
%	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
%	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
%	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
%	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
%	POSSIBILITY OF SUCH DAMAGE.

if nargin < 3
	error('Not enough input arguments.');
end

% default OPT arguments
a = -45;
c = 1;
scut = 0.2;
zmin = NaN;
zmax = NaN;
zcut = 0.5;
grey = 0.2*[1,1,1];
csea = [];
fs = 10;	% tick label fontsize

dec = 0;
dms = 0;
scale = 0;
inter = 0;
lake = 0;
decimflag = 0;
decim = 0;

novalue_color = [0,0,0];

if ~isnumeric(x) | ~isnumeric(y) | ~isnumeric(z)
	error('X,Y and Z must be numeric.')
end

if all(size(x) ~= 1) | all(size(y) ~= 1)
	error('X and Y must be vectors, not matrix.')
end

if length(x) ~= size(z,2) | length(y) ~= size(z,1)
	error('If Z has a size of [M,N], X must have a length of N, and Y a length of M.')
end

if nargin > 3
	dec = any(strcmp(varargin,'dec'));
	dms = any(strcmp(varargin,'dms'));
	if dms & any(abs(y) > 91)
		error('With DMS option Y must be in valid latitudes interval (decimal degrees).')
	end
	scale = any(strcmp(varargin,'scale'));
	inter = any(strcmp(varargin,'interp'));
	lake = any(strcmp(varargin,'lake'));
	if any(strcmp(varargin,'nodecim'))
		decim = 1;
		decimflag = 1;
	end
	kdecim = find(strcmp(varargin,'decim'));
	if ~isempty(kdecim)
		decimflag = 1;
		if (kdecim + 1) <= nargin & isnumeric(varargin{kdecim+1})
			decim = round(varargin{kdecim+1});
			decimflag = 2;
		end
	end
end
nargs = decimflag + dec + dms + scale + lake + inter;

if (nargin - nargs) > 3
	opt = varargin{1};
	if ~isnumeric(opt)
		error('OPT = [A,C,S,ZMIN,ZMAX] argument must be numeric.');
	end
	if ~isempty(opt)
		a = opt(1);
	end
	if length(opt) > 1
		c = opt(2);
		if c < 0
			error('C argument must be positive.');
		end
	end
	if length(opt) > 2
		scut = opt(3);
		if scut < 0 | scut >= 100
			error('SCUT argument must be a positive percentage.');
		end
	end
	if length(opt) > 4
		zmin = opt(4);
		zmax = opt(5);
	end
	if length(opt) > 5
		zcut = opt(6);
		if zcut < 0 | zcut >= 100
			error('ZCUT argument must be a positive percentage.');
		end
	end
end

if (nargin - nargs) < 5
	cmap = [];
else
	cmap = varargin{2};
	if ~isnumeric(cmap) | (~isempty(cmap) & (size(cmap,2) ~= 3 | min(cmap(:)) < 0 | max(cmap(:)) > 1))
		error('CMAP must be a valid colormap (3-column [R,G,B] matrix with 0.0 to 1.0 values).')
	end
end

if (nargin - nargs) < 6
	novalue = NaN;
else
	novalue = varargin{3};
	if ~isnumeric(novalue) | numel(novalue) > 1
		error('NOVALUE must be scalar.')
	end
end

if (nargin - nargs) < 7
	if isempty(cmap)
		if exist('seacolor','file')
			csea = seacolor(256);
		else
			csea = [.7,.9,1];
		end
	end
else
	csea = varargin{4};
	if ~isnumeric(csea)
		error('Unknown option')
	elseif (~isempty(csea) & (size(csea,2) ~= 3 | min(csea) < 0 | max(csea) > 1))
		error('SEACOLOR must be a valid [R,G,B] vector with 0.0 to 1.0 values).')
	end
end

if isempty(cmap)
	if exist('landcolor','file')
		cmap = landcolor.^1.3;
	else
		cmap = jet(256);
	end
end



% decimates data to avoid disk swap/out of memory...
nmax = 1500;
if decim
	n = decim;
else
	n = ceil(sqrt(numel(z))/nmax);
end
if n > 1
	x = x(1:n:end);
	y = y(1:n:end);
	z = z(1:n:end,1:n:end);
	fprintf('DEM: on the plot data has been decimated by a factor of %d...\n',n);
end

z = double(z); % necessary for most of the following calculations...
z(z==novalue) = NaN;

if inter
	z = fillgap(x,y,z);
end

if isempty(csea)
	k = (z~=0 & ~isnan(z));
else
	k = ~isnan(z);
end

if isnan(zmin)
	zmin = nmedian(z(k),zcut/100);
end
if isnan(zmax)
	zmax = nmedian(z(k),1 - zcut/100);
end
dz = zmax - zmin;

if dz > 0
	% builds the colormap: concatenates seacolor and landcolor around 0
	if ~isempty(csea) & zmin < 0 & zmax > 0
		l = size(csea,1);
		r = size(cmap,1)*abs(zmin)/zmax/l;
		cmap = cat(1,interp1(1:l,csea,linspace(1,l,round(l*r)),'*linear'),cmap);
	end
	
	% normalisation of Z using CMAP and convertion to RGB
	I = ind2rgb(uint16((z - zmin)*(length(cmap)/dz)),cmap);
	
	if c > 0
		% computes lighting from elevation gradient
		[fx,fy] = gradient(z,x,y);
		%fx = filter([1,0,0,0,-1],1,rf(z'))';
		%fy = filter([1,0,0,0,-1],1,rf(z));
		fxy = -fx*sind(a) - fy*cosd(a);
		clear fx fy	% free some memory...
		
		% lake option: zero gradient
		if lake
			dx = diff(z,1,2);
			dy = diff(z,1,1);
			u1 = ones(size(z,1),1);
			u2 = ones(1,size(z,2));
			z(cat(1,u2,dy)==0 & cat(1,dy,u2)==0 & cat(2,dx,u1)==0 & cat(2,u1,dx)==0) = 0;
			clear dx dy	% free some memory...
		end

		fxy(isnan(fxy)) = 0;

		% computes maximum absolute gradient (median-style), normalizes, saturates and duplicates in 3-D matrix
		r = repmat(max(min(fxy/nmedian(abs(fxy),1 - scut/100),1),-1),[1,1,3]);
	
		% applies contrast using exponent
		rp = (1 - abs(r)).^c;
		I = I.*rp;
	
		% lighter for positive gradient
		k = find(r > 0);
		I(k) = I(k) + (1 - rp(k));
				
	end
	
	% set novalues / NaN to black color
	[i,j] = find(isnan(z));
	if ~isempty(i)
		I(sub2ind(size(I),repmat(i,1,3),repmat(j,1,3),repmat(1:3,size(i,1),1))) = repmat(novalue_color,size(i,1),1);
	end
	% set the seacolor for 0 values
	if ~isempty(csea)
		[i,j] = find(z==0);
		if ~isempty(i)
			I(sub2ind(size(I),repmat(i,1,3),repmat(j,1,3),repmat(1:3,size(i,1),1))) = repmat(csea(end,:),size(i,1),1);
		end
	end

	hh = imagesc(x,y,I);
else
	hh = imagesc(x,y,z);
	colormap(cmap);
	text(mean(x),mean(y),'SPLASH!','Color','c','FontWeight','bold','HorizontalAlignment','center')
end

orient tall
axis xy, axis equal, axis tight

xlim = [min(x),max(x)];
ylim = [min(y),max(y)];
zlim = [min(z(:)),max(z(:))];

% axis basemap style
if dec | dms
	axis off

	if dms
		% approximates X-Y aspect ratio for this latitude (< 20-m precision for 1x1� grid)
		xyr = cos(mean(y)*pi/180);
	else
		xyr = 1;
	end
	set(gca,'DataAspectRatio',[1,xyr,1])
	bwy = 0.008*diff(ylim); % Y border width = 1%
	bwx = bwy/xyr; % border width (in degree of longitude)

	% transparent borders
	patch([xlim(1)-bwx,xlim(2)+bwx,xlim(2)+bwx,xlim(1)-bwx],ylim(1) - bwy*[0,0,1,1],'k','FaceColor','none','clipping','off')
	patch([xlim(1)-bwx,xlim(2)+bwx,xlim(2)+bwx,xlim(1)-bwx],ylim(2) + bwy*[0,0,1,1],'k','FaceColor','none','clipping','off')
	patch(xlim(1) - bwx*[0,0,1,1],[ylim(1)-bwy,ylim(2)+bwy,ylim(2)+bwy,ylim(1)-bwy],'k','FaceColor','none','clipping','off')
	patch(xlim(2) + bwx*[0,0,1,1],[ylim(1)-bwy,ylim(2)+bwy,ylim(2)+bwy,ylim(1)-bwy],'k','FaceColor','none','clipping','off')

	dlon = {'E','W'};
	dlat = {'N','S'};

	if dec
		ddx = dtick(diff(xlim));
		ddy = dtick(diff(ylim));
	else
		ddx = dtick(diff(xlim),1);
		ddy = dtick(diff(ylim),1);
	end

	xtick = (ddx*ceil(xlim(1)/ddx)):ddx:xlim(2);
	for xt = xtick(1:2:end)
		dt = ddx - max(0,xt + ddx - xlim(2));
		patch(repmat(xt + dt*[0,1,1,0]',[1,2]),[ylim(1) - bwy*[0,0,1,1];ylim(2) + bwy*[0,0,1,1]]','k','clipping','off')
		text(xt,ylim(1) - bwy,deg2dms(xt,dlon,dec),'FontSize',fs,'HorizontalAlignment','center','VerticalAlignment','top');
	end

	ytick = (ddy*ceil(ylim(1)/ddy)):ddy:ylim(2);
	for yt = ytick(1:2:end)
		dt = ddy - max(0,yt + ddy - ylim(2));
		patch([xlim(1) - bwx*[0,0,1,1];xlim(2) + bwx*[0,0,1,1]]',repmat(yt + dt*[0,1,1,0]',[1,2]),'k','clipping','off')
		text(xlim(1) - 1.1*bwx,yt,deg2dms(yt,dlat,dec),'FontSize',fs,'HorizontalAlignment','right','VerticalAlignment','middle');
	end
end

% scale legend
if scale
	%wsc = diff(xlim)*0.01;
	wsc = bwx;
	xsc = xlim(2) + wsc*4;

	% elevation scale (colorbar)
	zscale = linspace(zlim(1),zlim(2),length(cmap));
	yscale = linspace(0,diff(ylim)/2,length(cmap));
	ysc = ylim(1);
	ddz = dtick(dz*max(0.5*xyr*diff(xlim)/yscale(end),1));
	ztick = (ddz*ceil(zlim(1)/ddz)):ddz:zlim(2);
	patch(xsc + repmat(wsc*[-1;1;1;-1],[1,length(cmap)]), ...
		ysc + [repmat(yscale,[2,1]);repmat(yscale + diff(yscale(1:2)),[2,1])], ...
		repmat(zscale,[4,1]), ...
		'EdgeColor','flat','LineWidth',.1,'FaceColor','flat','clipping','off')
	colormap(cmap)
	caxis([zmin,zmax])
	patch(xsc + wsc*[-1,1,1,-1],ysc + yscale(end)*[0,0,1,1],'k','FaceColor','none','Clipping','off')
	text(xsc + 2*wsc + zeros(size(ztick)),ysc + (ztick - zlim(1))*0.5*diff(ylim)/diff(zlim),num2str(ztick'), ...
		'HorizontalAlignment','left','VerticalAlignment','middle','FontSize',8)
	
	% distance scale (in case of DMS only)
	if dms
		degkm = 6370*pi/180;
		dkm = dtick(diff(ylim)*degkm);
		ysc = ylim(2) - 0.5*dkm/degkm;
		patch(xsc + wsc*[-1,-1,0,0],ysc + dkm*0.5*[-1,1,1,-1]/degkm,'k','FaceColor',grey,'clipping','off')
		if dkm > 1
			skm = sprintf('%g km',dkm);
		else
			skm = sprintf('%g m',dkm*1000);
		end
		text(xsc,ysc,skm,'rotation',-90,'HorizontalAlignment','center','VerticalAlignment','bottom', ...
			'Color',grey,'FontWeight','bold')
	end

end


if nargout > 0
	h = hh;
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = nmedian(x,n)
%NMEDIAN Generalized median filter
%	NMEDIAN(X,N) sorts elemets of X and returns N-th value (N normalized).
%	So:
%	   N = 0 is minimum value
%	   N = 0.5 is median value
%	   N = 1 is maximum value

if nargin < 2
	n = 0.5;
end
y = sort(x(:));
y = interp1(sort(y),n*(length(y)-1) + 1);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function dd = dtick(dlim,deg)
%DTICK Tick intervals

if nargin < 2
	deg = 0;
end

if deg & dlim <= 2/60
	% less than 2 minutes: base 36
	m = 10^floor(log10(dlim*36))/36;
elseif deg & dlim <= 2
	% less than 2 degrees: base 6
	m = 10^floor(log10(dlim*6))/6;
else
	% more than few degrees or not degrees: decimal rules
	m = 10^floor(log10(dlim));
end
p = ceil(dlim/m);
if p <= 1
	dd = .1*m;
elseif p == 2
	dd = .2*m;
elseif p <= 5
	dd = .5*m;
else
	dd = m;
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function s = deg2dms(x,ll,dec)
%DEG2DMS Degree/minute/second display

if dec
	s = sprintf('%7.7g',x);
else
	xa = abs(x) + 1/360000;
	sd = sprintf('%d%c',floor(xa),176);	% ASCII char 176 is the degree sign
	sm = '';
	ss = '';
	if mod(x,1)
		sm = sprintf('%02d''',floor(mod(60*xa,60)));
		sa = floor(mod(3600*xa,60));
		if sa
			ss = sprintf('%02d"',sa);
		else
			if strcmp(sm,'00''')
				sm = '';
			end
		end
	end
	s = [sd,sm,ss,ll{1+int8(x<0)}];
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function z = fillgap(x,y,z)
% GRIDDATA is not efficient for large arrays, but has great advantage to be
% included in Matlab core functions! To optimize interpolation, we
% reduce the number of relevant data by building a mask of surrounding
% pixels of novalue areas... playing with linear index!

sz = size(z);
k = find(isnan(z));
k(k == 1 | k == numel(z)) = []; % removes first and last index (if exist)
if ~isempty(k)
	[xx,yy] = meshgrid(x,y);
	mask = zeros(sz,'int8');
	k2 = ind90(sz,k); % k2 is linear index in the row order
	% sets to 1 every previous and next index, both in column and row order
	mask([k-1;k+1;ind90(fliplr(sz),[k2-1;k2+1])]) = 1; 
	mask(k) = 0; % removes the novalue index
	kb = find(mask); % keeps only border values
	z(k) = griddata(xx(kb),yy(kb),z(kb),xx(k),yy(k));
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function k2 = ind90(sz,k)

[i,j] = ind2sub(sz,k);
k2 = sub2ind(fliplr(sz),j,i); % switched i and j: k2 is linear index in row order
