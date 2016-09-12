function f = objfun_linear(x,optParams)

%note, this guy is being minimized
%f = norm(x);
% load('OptParams.mat');

if(optParams.robCost)
traj = reshape(x(1:optParams.dim*optParams.len),optParams.dim,optParams.len);
f1 = alt_getRobustnessP_vector(traj,optParams.P1,optParams.Params_P1,0);
else
f1 = 0;
end
%f2 = alt_getRobustnessP_vector(traj,optParams.P2,optParams.Params_P2,0);
%f = SoftMin([f1,f2]);
%x
%f1
f2 = (optParams.gamma)*norm(x(1:optParams.dim*optParams.len))^2; %weighted sos of states
f = -f1+f2; %min robustness, robustness = not in P1
