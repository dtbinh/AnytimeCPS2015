function [r_P,r_P_der] = robustness_always_SafeDist(traj,d_min,need_derivative)
% robustness for always_I norm(p1-p2)^2>=dmin^2
%trajectory Sx (n*N) (n = sys dim, N = steps)
%%
% if(nargin==2)
%    need_derivative = 0; 
% end
r_P_der = [];
%%
dists_sqd = zeros(size(traj,2),1);

parfor t = 1:size(traj,2) %for all time steps
p1 = traj(1:3,t);
p2 = traj(4:6,t);
dists_sqd(t) = norm(p1-p2)^2;
end
Sd = dists_sqd-d_min^2; %robustness = min_I ( norm(p1-p2)^2 - d_min^2)
[r_P,C] = SoftMin(Sd);


%% derivative too
 der = need_derivative; %to be replaced by nargout
if(der)
    
end