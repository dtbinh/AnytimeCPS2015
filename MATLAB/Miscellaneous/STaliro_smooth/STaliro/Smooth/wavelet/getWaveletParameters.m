function wavparams = getWaveletParameters(SmoothOpt,genCode)

%%
for i = 1:numel(SmoothOpt.preds.Sets) %for all predicates

dim = size(SmoothOpt.preds.Sets(i).A,2); %dim of pred if not scalar

xmin = 2*SmoothOpt.preds.WavParams(i).x_min; %extend range for numerical stability
xmax = 2*SmoothOpt.preds.WavParams(i).x_max;
dx = SmoothOpt.preds.WavParams(i).dx;
grid_x = xmin:dx:xmax; %compute on this grid

dist_array_xy = zeros(numel(grid_x)*ones(1,dim));
E_dash = double(getcondvects(dim));

optional = SmoothOpt.preds.WavParams(i);

if(genCode)
    cfg=coder.config('mex');
        
    %for get coeffs (grid_x,dist_array_xy,dx,j_min,j_max,k_min,k_max,E_dash,0);
    arg_ins = {coder.typeof(grid_x,[1, Inf]),coder.typeof(dist_array_xy,Inf(1,dim)),coder.typeof(dx),...
       coder.typeof(optional.j_min),coder.typeof(optional.j_max),...
       coder.typeof(optional.k_min), coder.typeof(optional.k_max), coder.typeof(E_dash,Inf(1,dim)),...
       coder.typeof(0)};
   %coder.varsize('grid_x',[1 10^5],[0 1]);
    codegen -config cfg alt_getCoefficientsVector_genable -report -args arg_ins
        
end

optional.filename = [];
optional.savefile = 'temp.mat';
optional.k_min = SmoothOpt.preds.WavParams(i).k_min;
optional.k_max = SmoothOpt.preds.WavParams(i).k_max;
optional.j_min = SmoothOpt.preds.WavParams(i).j_min;
optional.j_max = SmoothOpt.preds.WavParams(i).j_max; %2 works well in R2
PredSet = Polyhedron('A',SmoothOpt.preds.Sets(i).A,'b',SmoothOpt.preds.Sets(i).b);
viz = 1;
wavparams(i) = WavSignedDistVector_Rn(PredSet,xmin,xmax,dx,viz,optional);





end

