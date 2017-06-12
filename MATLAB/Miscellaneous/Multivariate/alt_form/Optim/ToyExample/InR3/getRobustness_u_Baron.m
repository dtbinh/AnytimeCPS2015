function out = getRobustness_u_Baron(u, obs, goal, optParams)  

% path is an array of points in R^3 with length N (discrete time)
path = reshape(optParams.A_x0*optParams.x0 + optParams.B_U*u,3,20)';
%% path = reshape(u,19,3);
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
        uQ = -xc(n,1:3) + obs{o}.ub;
        lQ = xc(n,1:3) - obs{o}.lb;
        dist_diag = [uQ lQ];
        
        d1(n,o) = -SmoothMin(dist_diag,50);
    end
end

out1 = SmoothMin(d1(:),50);

%% Eventually Get to Goal



for n = 1:N
    guQ = xc(n,1:3) - gub;
    glQ = xc(n,1:3) - glb;
    dist_mat = (gA*[guQ' guQ' guQ' glQ' glQ' glQ']);
    dist_diag = diag(dist_mat);
    d2(n) = SmoothMin(dist_diag,50);
end

out2 = SmoothMax(d2,50);

out = SmoothMin([out1 out2],50);
out = -out; %negate for SmoothMaximization
end
