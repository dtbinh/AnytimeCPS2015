P = Polyhedron('lb',[-1 -1],'ub',[1 1]);
xmax = 2;
xmin = -2;
ymax = 2;
ymin = -2;
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
a = arrayfun(@(x,y) mexHatWav([x;y]), msg_x(:), msg_y(:));
mexhat = reshape(a,numel(grid_x),numel(grid_y));
mesh(grid_x,grid_y,mexhat)
%% get coeffs (loopy)
j_low = 0;%-10;
j_up = 10;
dj = 1;
k_low = -10;
k_up = 10;
dk = 1;

f_times_psi = zeros(numel(grid_x),numel(grid_y));
theta_jk = zeros(numel(j_low:dj:j_up), numel(k_low:dk:k_up));
ct_j = 0;
ct_k = 0;

for j = j_low:dj:j_up %scale
    ct_j = ct_j+1;
    ct_k = 0;
    for k = k_low:dk:k_up %disp
        ct_k = ct_k+1;
        %compute coeffs
        for xix = 1:numel(grid_x)
            for yix = 1:numel(grid_y)
                x = grid_x(xix);
                y = grid_y(yix);
                weird_pt = ((2^j)*[x;y])-k;
                psi_jk_xy = (2^(j/2))*mexHatWav(weird_pt);
                f_times_psi(xix,yix) = dist_array_xy(xix,yix)*psi_jk_xy;
            end
        end
        theta_jk(ct_j,ct_k) = dx*dy*sum(f_times_psi(:));
    end
end
mesh((k_low:dk:k_up)',(j_low:dj:j_up)',theta_jk);
xlabel('k');ylabel('j');zlabel('theta_{jk}')
%% compute fhat on grid
J = j_low:dj:j_up;
K = k_low:dk:k_up;
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
a = arrayfun(@(x,y) Beta_fhat_x([x;y], theta_jk,dist_array_xy,dx,dy,J,K), msg_x(:), msg_y(:));
fhat_array_xy = reshape(a,numel(grid_x),numel(grid_y));
mesh(grid_x,grid_y,fhat_array_xy);