

%% codegen for
%alt_getRobustnessP_vector_genable_parallel(traj,P,wavparams,exact)


cfg=coder.config('mex');
arg_ins = {coder.typeof(traj),coder.typeof(P),coder.typeof(wavparams),coder.typeof(0)};
%coder.varsize('grid_x',[1 10^5],[0 1]);
codegen -config cfg alt_getRobustnessP_vector_genable_parallel -report -args arg_ins
%%
%parallel was faster
codegen -config cfg alt_getRobustnessP_vector_genable -report -args arg_ins

%%
%alt_getRobustnessP_and_der_vector_genable(traj,wavparams)
arg_ins = {coder.typeof(traj),coder.typeof(wavparams),coder.typeof(0)};
codegen -config cfg alt_getRobustnessP_and_der_vector_genable -report -args arg_ins
%% for eventually
%robustness_eventually_P_genable(traj,wavparams,need_derivative)
arg_ins = {coder.typeof(traj),coder.typeof(wavparams),coder.typeof(0)};
codegen -config cfg robustness_eventually_P_genable -report -args arg_ins

%% parallel
arg_ins = {coder.typeof(traj),coder.typeof(wavparams),coder.typeof(0)};
codegen -config cfg robustness_eventually_P_genable_parallel -report -args arg_ins

%% objfun2_toy_using_mex(x,optParams)
arg_ins = {coder.typeof(x_0),coder.typeof(optParams),coder.typeof(1)};
codegen -config cfg objfun2_toy_genable -report -args arg_ins
