function [f,g_out] = alternate_objfun2_u_toy_linear(u,optParams)
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

%rho_1 = zeros(optParams.len,1);
%rho_2 = zeros(optParams.len,1);

    for t=1:optParams.len
       rho_1(t) = -SoftMin([1-traj(1,t), traj(1,t)+1,1-traj(2,t), traj(2,t)+1]);
       rho_2(t) = +SoftMin([2.5-traj(1,t), traj(1,t)-2,2.5-traj(2,t), traj(2,t)-2]); 
       
    end
    rob = SoftMin([SoftMin(rho_1),SoftMax(rho_2)]);


else % if no robustness in cost
f1 = 0;f2=0;rob=0;
end

f3 = 0;%(optParams.gamma)*norm(u)^2; %2-norm sqd of u
%f3=0; %why is this hard-coded mate?
f = -rob+f3; %min neg of robustness, robustness = not in P1

g_out= -g+2*u*optParams.gamma; %FIX!!!!

