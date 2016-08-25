%% get coeffs (loopy), 2 k's
j_low = -30;%-10;
j_up = 30;
dj = 1;
k_low = -50;
k_up = 50;
dk = 1;

f_times_psi = zeros(numel(grid_x),numel(grid_y));
theta_jk = zeros(numel(j_low:dj:j_up), numel(k_low:dk:k_up), numel(k_low:dk:k_up));

ct_j = 0;
ct_k1 = 0;
ct_k2 = 0;
for j = j_low:dj:j_up %scale
    ct_j = ct_j+1;
    ct_k1 = 0; 
    ct_k2 = 0;
    for k1 = k_low:dk:k_up %disp
        ct_k1 = ct_k1+1;
        ct_k2 = 0;
        for k2 = k_low:dk:k_up
            ct_k2 = ct_k2+1;
        %compute coeffs
        [j k1 k2]
        for xix = 1:numel(grid_x)
            for yix = 1:numel(grid_y)
                x = grid_x(xix);
                y = grid_y(yix);
                weird_pt = ((2^j)*[x;y])-[k1;k2];
                psi_jk_xy = (2^(j/2))*mexHatWav(weird_pt);
                f_times_psi(xix,yix) = dist_array_xy(xix,yix)*psi_jk_xy;
            end
        end
        theta_jk(ct_j,ct_k1,ct_k2) = dx*dy*sum(f_times_psi(:));
        end
    end
end
%mesh((k_low:dk:k_up)',(j_low:dj:j_up)',theta_jk);
%xlabel('k');ylabel('j');zlabel('theta_{jk}')

%% disp
for j = 1:numel(j_low:dj:j_up)
sz = numel(k_low:dk:k_up);
temp = reshape(theta_jk(j,:,:),sz,sz);
mesh((k_low:dk:k_up)',(k_low:dk:k_up)',temp)
pause(.5);
end

%% recreate
J = j_low:dj:j_up;
K = k_low:dk:k_up;
[msg_x,msg_y] = meshgrid(grid_x,grid_y);
a = arrayfun(@(x,y) Beta_fhat_x([x;y], theta_jk,dist_array_xy,dx,dy,J,K), msg_x(:), msg_y(:));
fhat_array_xy = reshape(a,numel(grid_x),numel(grid_y));
mesh(grid_x,grid_y,fhat_array_xy);


