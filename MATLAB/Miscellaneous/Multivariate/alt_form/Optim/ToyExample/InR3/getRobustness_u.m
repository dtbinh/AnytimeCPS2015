function out = getRobustness_u(u, obs, goal, optParams)  

% path is an array of points in R^3 with length N (discrete time)
path = reshape(optParams.A_x0*optParams.x0 + optParams.B_U*u,optParams.dim, ...
    optParams.len)';


N = size(path, 1);
numObs = size(obs, 1);

% Goal is a cube space around the goal point.
ds = 1;
glb = goal.stop' - goal.ds';
gub = goal.stop' + goal.ds';
gA = [-eye(3);eye(3)];

xc = path;
%% Avoid unsafe Region
% For each point in the path SoftMaximize the sphere region that avoids
% collision with an obstacle

d1 = zeros(N, numObs);

for n = 1:N
    for o = 1:numObs
        A = (obs{o}.A);
        uQ = xc(n,1:3) - obs{o}.ub;
        lQ = xc(n,1:3) - obs{o}.lb;
        dist_mat = (A*[uQ' uQ' uQ' lQ' lQ' lQ']);
        dist_diag = diag(dist_mat);
        d1(n,o) = -SoftMin(dist_diag,10);
    end
end

out1 = SoftMin(d1(:),10);

%% Eventually Get to Goal

d2 = zeros(N, 1);

for n = 1:N
    guQ = xc(n,1:3) - gub;
    glQ = xc(n,1:3) - glb;
    dist_mat = (gA*[guQ' guQ' guQ' glQ' glQ' glQ']);
    dist_diag = diag(dist_mat);
    d2(n) = SoftMin(dist_diag,10);
end

out2 = SoftMax(d2,10);

out = SoftMin([out1 out2],10);
out = -out; %negate for SoftMaximization
end
