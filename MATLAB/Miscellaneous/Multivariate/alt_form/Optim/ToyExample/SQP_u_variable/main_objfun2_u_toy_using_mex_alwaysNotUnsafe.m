function [f,g_out] = main_objfun2_u_toy_using_mex_alwaysNotUnsafe(u,optParams)
% x is the entire search vector, including inputs

%note, this guy is being minimized
%f = norm(x);
% load('OptParams.mat');



%%
%get states
x = optParams.A_x0*optParams.x0 + optParams.B_U*u;

%%

% make input
g = zeros(numel(u),1);
if(optParams.robCost)
traj = reshape(x(1:optParams.dim*optParams.len),optParams.dim,optParams.len);

if(nargout>1)
[f1,g1] = alt_getRobustnessP_and_der_vector_genable_parallel_mex(traj,optParams.Params_P_unsafe,1);
%[f2,g2]= robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,1); %1 for der
%[rob,C] = SoftMin([f1 f2]);
rob = f1;
%df_by_dx = (exp(-C*f1)*g1 + g2*exp(-C*f2))/(exp(-C*f1)+exp(-C*f2));
df_by_dx = g1;
g = optParams.B_U'*df_by_dx; %grad of robustness wrt u

else
P = [];
f1 = alt_getRobustnessP_vector_genable_parallel_mex(traj,P,optParams.Params_P_unsafe,0);
%f2 = robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,0);
%rob = SoftMin([f1 f2]);
rob = f1;
end

else % if no robustness in cost
f1 = 0;f2=0;rob=0;
end

f3 = (optParams.gamma)*norm(u)^2; %2-norm sqd of u
%f3=0; %why is this hard-coded mate?
f = -rob+f3; %min neg of robustness, robustness = not in P1

g_out= -g+2*u*optParams.gamma; %FIX!!!!

