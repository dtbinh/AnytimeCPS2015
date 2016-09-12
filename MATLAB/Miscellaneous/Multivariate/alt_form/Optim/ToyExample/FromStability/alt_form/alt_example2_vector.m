% example 2
%(always not P1) AND/OR (min/max) (always not P2)
P1 = Polyhedron('lb',[-2 -2],'ub',[-1 -1]);
P2 = Polyhedron('lb',[1 1],'ub',[2 2]);
xmin = -5;
xmax = 5;
dx = 0.1;

optional_P1.filename = 'P1.mat';
optional_P1.savefile = 'P1.mat';
optional_P2.filename = 'P2.mat';
optional_P2.savefile = 'P2.mat';


[Params_P1] = WavSignedDistVector(P1,xmin,xmax,dx,0,optional_P1);
[Params_P2] = WavSignedDistVector(P2,xmin,xmax,dx,0,optional_P2);
%pause;
close all;clc;
%plot(P1);hold all;plot(P2);

%% gen trajs
Ntrials = 100;
len = 10;
dim  = size(P1.A,2);
x_lb = -2.5;
x_ub = 2.5;
u_lb = -0.32;
u_ub = 0.32;
Nx = 2;
Nu = 2;
A = eye(2);
B = eye(2);

[Traj_all,U_all] = getTrajectories(A,B,x_lb,x_ub,u_lb,u_ub,Nx,Nu,len,Ntrials);
%% get rob
parfor i = 1:Ntrials
i
%trajec(:,:,i) = 0.5*randn(len,dim);
traj = Traj_all(:,:,i);

r_exact_P1 = alt_getRobustnessP_vector(traj,P1,Params_P1,1);
r_approx_P1 = alt_getRobustnessP_vector(traj,P1,Params_P1,0);

r_exact_P2 = alt_getRobustnessP_vector(traj,P2,Params_P2,1);
r_approx_P2 = alt_getRobustnessP_vector(traj,P2,Params_P2,0);

r_phi_exact = max(r_exact_P1,r_exact_P2);
r_phi_approx = SoftMax([r_approx_P1,r_approx_P2]);
err(i) = r_phi_exact-r_phi_approx;
err_rel(i) = (r_phi_exact-r_phi_approx)/abs(r_phi_exact);
end
%[mean(abs(err)) std(abs(err))]
[mean(err_rel) std(err_rel)]
figure;
hist(err_rel);grid on;
