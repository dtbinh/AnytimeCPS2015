% example 2
% inP1 until_[I] inP2

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

%%
clear err err_rel trajec traj;

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
'got rand trajs'

%%
mins_soft = zeros(len,1);
mins_exact = zeros(len,1);
for i = 1:Ntrials
i    
    %trajec(:,:,i) = 0.5*randn(len,dim);
    traj = Traj_all(:,:,i);
    
    for t_dash = 1:len
        traj_for2 = traj(:,t_dash);
        r_exact_P2 = alt_getRobustnessP_vector_in(traj_for2,P2,Params_P2,1);
        r_approx_P2 = alt_getRobustnessP_vector_in(traj_for2,P2,Params_P2,0);
        
        if(t_dash>1)
%             traj(:,t_dash-1,:);
            traj(:,1:t_dash-1);
            r_exact_P1 = alt_getRobustnessP_vector_in(traj_for1,P1,Params_P1,1);
            r_approx_P1 = alt_getRobustnessP_vector_in(traj_for1,P1,Params_P1,0);
            mins_soft(t_dash) = SoftMin([r_approx_P2,r_approx_P1]);
            mins_exact(t_dash) = min(r_exact_P2,r_exact_P1);
        else
            mins_soft(t_dash) = r_approx_P2;
            mins_exact(t_dash) = r_exact_P2;
        end
        
    end
    r_phi_exact = max(mins_exact);
    r_phi_approx = SoftMax(mins_soft);
    
    err(i) = r_phi_exact-r_phi_approx;
    err_rel(i) = (r_phi_exact-r_phi_approx)/abs(r_phi_exact);
end
%[mean(abs(err)) std(abs(err))]
[mean(err_rel) std(err_rel)]
figure;
hist(err_rel);grid on;
fname = strcat('RobTest_N',num2str(len),'_P1_until_P2.mat');
save(fname,'err','err_rel','len','Traj_all','U_all');
