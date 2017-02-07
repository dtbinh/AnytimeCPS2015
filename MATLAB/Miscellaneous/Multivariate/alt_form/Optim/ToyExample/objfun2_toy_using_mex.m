function [f,g] = objfun2_toy_using_mex(x,optParams)
% x is the entire search vector, including inputs

%note, this guy is being minimized
%f = norm(x);
% load('OptParams.mat');



%%
global ct;
ct = ct+1;
g = zeros(numel(x),1);

if(optParams.robCost)
traj = reshape(x(1:optParams.dim*optParams.len),optParams.dim,optParams.len);
%f1 = alt_getRobustnessP_vector(traj,optParams.P1,optParams.Params_P1,0);

if(nargout>1)
[f1,g1] = alt_getRobustnessP_and_der_vector_genable_parallel_mex(traj,optParams.Params_P_unsafe,1);
[f2,g2]=robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,1); %1 for der
[rob,C] = SoftMin([f1 f2]);
df_by_dx = (exp(-C*f1)*g1 + g2*exp(-C*f2))/(exp(-C*f1)+exp(-C*f2));
g_temp = df_by_dx;
else %no der
g_temp = zeros(optParams.dim*optParams.len,1);
P = [];
f1 = alt_getRobustnessP_vector_genable_parallel_mex(traj,P,optParams.Params_P_unsafe,0);
f2 = robustness_eventually_P_genable_parallel_mex(traj,optParams.Params_P_term,0);
rob = SoftMin([f1 f2]);
end

else % if no robustness in cost
f1 = 0;f2=0;rob=0;g_temp = zeros(optParams.dim*optParams.len,1);
end
%f2 = alt_getRobustnessP_vector(traj,optParams.P2,optParams.Params_P2,0);
%f = SoftMin([f1,f2]);
%x
%f1
f3 = (optParams.gamma)*norm(x(1:optParams.dim*optParams.len))^2; %weighted sos of states
f = -rob+f3; %min neg of robustness, robustness = not in P1
g(1:optParams.dim*optParams.len) = -g_temp+2*x(1:optParams.dim*optParams.len)*optParams.gamma; %FIX!!!!
%g(optParams.dim*optParams.len+1:end) = -optParams.B_U'*g_temp; %comment out
