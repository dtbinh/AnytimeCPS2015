%%
P = Polyhedron('lb',[-1 -1],'ub',[1 1]);
xmax = 3;
xmin = -3;
ymax = 3;
ymin = -3;
dx = 0.25;
dy = 0.25;

dim = size(P.A,2);

grid_x = xmin:dx:xmax;
grid_y = ymin:dy:ymax;
tic;


%% get signed dist
if(exist('dist_array_xy_vec') &&  sum(size(dist_array_xy_vec) == size(meshgrid(grid_x,grid_y))) == dim)
    
'already have data'
else
    'computing dist'
dist_array_xy = zeros(numel(grid_x),numel(grid_y));
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
if(exist('Staliro')>0)
   [msg_x,msg_y] = meshgrid(grid_x,grid_y);
   a = arrayfun(@(x,y) SignedDist([x;y],P.A,P.b), msg_x(:), msg_y(:));
   dist_array_xy_vec = reshape(a,numel(grid_x),numel(grid_y)); 
   dist_array_xy = dist_array_xy_vec;  
end
if(dim==2)
    figure;
   mesh(grid_x,grid_y,dist_array_xy_vec); 
end

end
%% get coefficients
'getting coeffs'
E_dash = double(getcondvects(dim)); %set of vertices of [0,1]^dim
E = E_dash(2:end,:); % set of non-zero vertices in E_dash
k_min = -10;
k_max = +10;
j_min = 0;
j_max = 0;

E = E_dash; %test
C_ejk = getCoefficientsVector(grid_x,dist_array_xy,dx,j_min,j_max,k_min,k_max,E,0);

%% test on grid
'visualizing approximation'
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
if(exist('Staliro')>0)
   [msg_x,msg_y] = meshgrid(grid_x,grid_y);
   a = arrayfun(@(x,y) getWavApprox_vector([x;y],C_ejk,k_min,k_max,j_min,j_max,E), msg_x(:), msg_y(:));
   fhat_array = reshape(a,numel(grid_x),numel(grid_y)); 
   
end
if(dim==2)
    figure;
   mesh(grid_x,grid_y,fhat_array); 
   figure;
   mesh(grid_x,grid_y,dist_array_xy-fhat_array);
end

