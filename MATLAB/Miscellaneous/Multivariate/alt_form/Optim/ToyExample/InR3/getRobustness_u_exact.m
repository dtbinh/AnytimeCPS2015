function out = getRobustness_u_exact(u, obs, goal, optParams)  

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
% For each point in the path maximize the sphere region that avoids
% collision with an obstacle

d1 = zeros(N, numObs);

for n = 1:N
    for o = 1:numObs
        A = (obs{o}.A);
        uQ = xc(n,1:3) - obs{o}.ub;
        lQ = xc(n,1:3) - obs{o}.lb;
        dist_mat = (A*[uQ' uQ' uQ' lQ' lQ' lQ']);
        dist_diag = diag(dist_mat);
        d1(n,o) = -min(dist_diag);
    end
end

out1 = min(d1(:));

%% Eventually Get to Goal

d2 = zeros(N, 1);

for n = 1:N
    guQ = xc(n,1:3) - gub;
    glQ = xc(n,1:3) - glb;
    dist_mat = (gA*[guQ' guQ' guQ' glQ' glQ' glQ']);
    dist_diag = diag(dist_mat);
    d2(n) = min(dist_diag);
end

out2 = max(d2);

out = min([out1 out2]);
out = -out; %negate for maximization
end
