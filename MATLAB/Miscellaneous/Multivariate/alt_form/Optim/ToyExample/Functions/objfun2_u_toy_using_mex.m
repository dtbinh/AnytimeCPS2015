function [f,g] = objfun2_u_toy_using_mex(u,optParams)
% x is the entire search vector, including inputs

%note, this guy is being minimized
%f = norm(x);
% load('OptParams.mat');



%%
%get states
x_init_onwards = optParams.A_x0*optParams.x0 + optParams.B_U*u;
x = [optParams.x0;x_init_onwards];

% make input
g = zeros(numel(x),1);
if(optParams.robCost)
traj = reshape(x(1:optParams.dim*optParams.len),optParams.dim,optParams.len);

if(nargout>1)
[f1,g1] = alt_getRobustnessP_and_der_vector_genable_mex(traj,optParams.Params_P_unsafe,1);
[f2,g2]=robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,1); %1 for der
[rob,C] = SoftMin([f1 f2]);
df_by_dx = (exp(-C*f1)*g1 + g2*exp(-C*f2))/(exp(-C*f1)+exp(-C*f2));

else
g1 = 0;g2=0;
P = [];
f1 = alt_getRobustnessP_vector_genable_parallel_mex(traj,P,optParams.Params_P_unsafe,0);
f2 = robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,0);
rob = SoftMin([f1 f2]);
end

else % if no robustness in cost
f1 = 0;f2=0;rob=0;g1 = zeros(optParams.dim*optParams.len,1);g2=g1;
end

f3 = (optParams.gamma)*norm(x(1:optParams.dim*optParams.len))^2; %weighted sos of states
f3=0;
f = -rob+f3; %min neg of robustness, robustness = not in P1

g(1:optParams.dim*optParams.len) = -g1-g2+2*x(1:optParams.dim*optParams.len)*optParams.gamma; %FIX!!!!

