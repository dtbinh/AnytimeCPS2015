P = Polyhedron('lb',[-1 -1],'ub',[1 1]);
xmax = 10;
xmin = -10;
ymax = 10;
ymin = -10;
dx = 0.05;
dy = 0.05;

grid_x = xmin:dx:xmax;
grid_y = ymin:dy:ymax;
tic;
dist_array_xy = zeros(numel(grid_x),numel(grid_y));
%%
figure;

for i = 1:numel(grid_x)
    for j = 1:numel(grid_y)
        plot(grid_x(i),grid_y(j),'o');
        x_i = grid_x(i);
        y_j = grid_y(j);
        fprintf('computing dist for pt at idx %d, %d \n',i,j);
        [dist_array_xy(i,j),~] = getSignedDistance([x_i;y_j],P);
        hold on;
    
    end
end
t_loop = toc;
%% try vectorizing
tic
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
a = arrayfun(@(x,y) getSignedDistance([x;y],P), msg_x(:), msg_y(:));
dist_array_xy_vec = reshape(a,numel(grid_x),numel(grid_y));
t_vect = toc;
%% mex hat on the grid
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
a = arrayfun(@(x,y) mexHatWav([x;y],1), msg_x(:), msg_y(:));
mexhat = reshape(a,numel(grid_x),numel(grid_y));