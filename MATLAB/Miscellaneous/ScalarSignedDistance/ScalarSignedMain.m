%% def P
P = Polyhedron('lb',-1,'ub',1);

% region to compute over
xmax = 4;
xmin = -4;
dx = 0.05;
grid_x = xmin:dx:xmax;

%% compute signed distance on the line
tic
dist_array_x = arrayfun(@(x) getSignedDistance(x,P), grid_x);
toc
figure;
plot(grid_x,dist_array_x);grid on;

%% visualize RickerWavelet or MeyerWavelet
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
j_min = 0;
j_max = 3;
k_min = -20;
k_max = 20;

[C,D] = getCoefficientsScalar(grid_x,dist_array_x,dx, ...
    j_min,j_max,k_min,k_max,1);

%% compute fhat on line
%theta_jk = theta_jk/(sum(theta_jk(:))/2);
fhat_scalar = arrayfun(@(x) getWavApprox(x,C,D,k_min,k_max,j_min,j_max), ... 
    grid_x);
figure;
plot(grid_x,fhat_scalar);grid on;
hold all
plot(grid_x,dist_array_x);
legend('fhat','f');

