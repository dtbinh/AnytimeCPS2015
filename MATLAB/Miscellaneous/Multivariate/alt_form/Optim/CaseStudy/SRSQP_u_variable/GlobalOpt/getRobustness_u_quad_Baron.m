function out = getRobustness_u_quad_Baron(u, obs, goal, optParams)  
C = 30; %30 works best for map1
% path is an array of points in R^3 with length N (discrete time)
path_temp = reshape(optParams.A_x0*optParams.x0 + optParams.B_U*u,optParams.dim, ...
    optParams.len)';
path = path_temp(:,4:6); %where quad x y z are

N = size(path, 1);
numObs = size(obs, 1);

% Goal is a cube space around the goal point.
ds = 1;
glb = goal.stop' - goal.ds';
gub = goal.stop' + goal.ds';
gA = [-eye(3);eye(3)];

xc = path;
%% Avoid unsafe Region
% For each point in the path SmoothMaximize the sphere region that avoids
% collision with an obstacle



for n = 1:N
    for o = 1:numObs
        A = (obs{o}.A);
        uQ = xc(n,1:3) - obs{o}.ub;
        lQ = xc(n,1:3) - obs{o}.lb;
        dist_mat = (A*[uQ' uQ' uQ' lQ' lQ' lQ']);
        dist_diag = diag(dist_mat);
        d1(n,o) = -SmoothMin(dist_diag,C);
    end
end

out1 = SmoothMin(d1(:),C);

%% Eventually Get to Goal



for n = 1:N
    guQ = xc(n,1:3) - gub;
    glQ = xc(n,1:3) - glb;
    dist_mat = (gA*[guQ' guQ' guQ' glQ' glQ' glQ']);
    dist_diag = diag(dist_mat);
    d2(n) = SmoothMin(dist_diag,C);
end

out2 = SmoothMax(d2,C);

out = SmoothMin([out1 out2],C);
out = -out; %negate for SmoothMaximization
end
