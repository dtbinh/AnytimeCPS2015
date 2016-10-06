%Bldg main
%%
Ts = 60*60; %sampling time, 1 hr
H = 24; %24 hour, 1 step per hour
[A,B,Bd,C] = linear_model(Ts); 
disturbances = sim_disturbance(1999,4,1,1999,4,3); %disturbances for a day
U_feas = Polyhedron('lb',-500,'ub',2000);
P_feas = Polyhedron('lb',0*ones(4,1),'ub',50*ones(4,1));
dec_factor = 10;
P1_comfort = Polyhedron('lb',22,'ub',28);

load('ComfortParams.mat');

%% generate some code
genCodeCostFn = 0;
if(genCodeCostFn)
    cfg=coder.config('mex');
    x = 0;
    %for get coeffs (grid_x,dist_array_xy,dx,j_min,j_max,k_min,k_max,E_dash,0);
    arg_ins = {coder.typeof(x),coder.typeof(wavparams.C),coder.typeof(wavparams.D),...
         coder.typeof(wavparams.k_min),coder.typeof(wavparams.k_max), ...
         coder.typeof(wavparams.j_min),coder.typeof(wavparams.j_max)};
    codegen -config cfg getWavApprox -report -args arg_ins -o getWavApprox_mex
    %codegen -config cfg confun_case -report -args arg_ins -o confun_case_mex
end

%%
x_0 = 21*ones(4,1);
optParams.dim = 4;
optParams.len = 24;
optParams.A = A;
optParams.B = B*10; %check this
optParams.Bd = Bd;
optParams.P_feas = P_feas;
optParams.U_feas = U_feas;

x_feas = bldg_getFeasTraj(x_0,optParams,disturbances);




