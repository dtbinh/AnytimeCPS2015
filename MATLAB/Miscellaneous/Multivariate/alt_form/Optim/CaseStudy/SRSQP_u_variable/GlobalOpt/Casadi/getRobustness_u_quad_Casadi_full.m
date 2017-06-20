function out = getRobustness_u_quad_Casadi_full(w, obs, goal, optParams)  
import casadi.*
C = 30; %30 works best for map1
% path is an array of points in R^3 with length N (discrete time)
Nx = optParams.dim_x;
N = optParams.len;
x = w(1:optParams.len*optParams.dim_x);
path_temp = reshape(x(1:Nx*N),Nx,N)';
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


d1 = SX.sym('g',N,numObs);
for n = 1:N
    for o = 1:numObs
%         A = (obs{o}.A);
%         b = (obs{o}.b);
%         dist_diag = SX.sym('t',numel(b),1);
%         for i = 1:size(A,1)
%             dist_diag(i) = b(i) - A(i,:)*xc(n,:)';
%         end
%         d1(n,o) = -SmoothMin(dist_diag,C);
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


d2 = SX.sym('d',N,1);
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
% 
% if(out<=SX(-eps))
%     keyboard;
% end
end
