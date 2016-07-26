%% def P
P = Polyhedron('lb',-1,'ub',1);

% region to compute over
xmax = 3;
xmin = -3;
dx = 0.05;
grid_x = xmin:dx:xmax;

%% compute signed distance on the line
tic
dist_array_x = arrayfun(@(x) getSignedDistance(x,P), grid_x);
toc
figure;
plot(grid_x,dist_array_x);grid on;

%% visualize RickerWavelet
if(0)
ricker_wav = arrayfun(@(x) RickerWavelet(x), grid_x);
figure;
plot(grid_x,ricker_wav);grid on;
else
    [phi,psi] = arrayfun(@(x) MeyerWavelet(x), grid_x);
    figure;
    plot(grid_x,phi);hold all;
    plot(grid_x,psi);legend('phi','psi');grid on;
    
end
%% get coeffs of wav

%scale
j_low = -2;
j_up = 2;
dj = 1;

%disp
k_low = -20;
k_up = 20;
dk = 1;

J = j_low:dj:j_up;
K = k_low:dk:k_up;
%
f_times_psi = zeros(numel(grid_x),1);
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
            x = grid_x(xix);
            weird_pt = ((2^j)*x)-k;
            psi_jk_x = (2^(j/2))*RickerWavelet(weird_pt);
            f_times_psi(xix) = dist_array_x(xix)*psi_jk_x;
        end
        theta_jk(ct_j,ct_k) = dx*sum(f_times_psi(:));
    end
end
figure;
if(numel(J)>1)
mesh((k_low:dk:k_up)',(j_low:dj:j_up)',theta_jk);
xlabel('k');ylabel('j');zlabel('theta_{jk}')
else
plot(K,theta_jk);grid on;    
end


%% compute fhat on line
%theta_jk = theta_jk/(sum(theta_jk(:))/2);
fhat_scalar = arrayfun(@(x) fhat_scalar_x(x,theta_jk,dist_array_x,dx,J,K), ... 
    grid_x);
figure;
plot(grid_x,fhat_scalar);grid on;
hold all
plot(grid_x,dist_array_x);
legend('fhat','f');

