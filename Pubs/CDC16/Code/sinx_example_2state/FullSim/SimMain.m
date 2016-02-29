%Sim Main
'Preliminaries'
Prelims_no_b4m; %init everything
clc;close all;
%load('TempSets_par.mat');

'Initializing plant'
%init state for linearized system
z0 = T_diffeo([x1_0;x2_0],a);
x0 = T_inv_diffeo(z0,a);
if(x0~=[x1_0;x2_0]) %sanity check
    'Something is off'
end
%init estimate of x0
x0_hat = x0 + (mag)*(pi/180)*rand(numel(x0),1); %x0_hat = x0 + e0
z0_hat = T_diffeo(x0_hat,a);
%get reach set for x0 with error in there
X_0 = plus(x0_hat,-E);
X_0.minHRep;

%% get term cost
'Computing term cost'
Q = eye(size(A_d,2));
R = 10^(-4)*eye(size(B_d,2));
Q_term = dlyap((A_d-B_d*K_lqr_d),Q+K_lqr_d'*R*K_lqr_d);


%% mpc trial
'Init MPC'
Tsim = 100;
z_true = zeros(size(A_d,2),Tsim);
z_hat = zeros(size(A_d,2),Tsim);
x_true = zeros(size(A_d,2),Tsim);
x_hat = zeros(size(A_d,2),Tsim);
optval = zeros(Tsim,1);
v_applied = zeros(size(B_d,2),Tsim);
z_true(:,1) = z0;

figure(1);
stairs(Z);
hold on;
figure(2);
hold on;
pause(0.1);
for k = 1:Tsim-1
k
%measure plant
'Get measurements'
x_true(:,k) = T_inv_diffeo(z_true(:,k),a); %from lin dynamics
x_hat(:,k) = x_true(:,k) + (mag)*(pi/180)*rand(numel(x0),1);    %add estimation error in x, xhat=x+e
z_hat(:,k) = T_diffeo(x_hat(:,k),a); %into z_hat
X_k = plus(x_hat(:,k),-E); %setin which it true state lies given that measurement

%get constraints
'Get constraints'
[Zjk,V_in,Zreach,Xreach,E_tilde] = getZjs(x_hat(:,k),X_k,X,Z,E,W,U,V_inner_global,A_d,B_d,K_lqr_d,a,N);

%solve mpc
'Solve MPC'
[z_pred,v_pred,optval(k)] = NLRMPC(z_hat(:,k),Zjk,Z_f_worst,V_in,A_d,B_d,N,Q,Q_term,R);
v_applied(k) = v_pred(1); %apply first input

%apply input to plant, update state
'Apply to plant'
z_true(:,k+1) = linplant(A_d,B_d,z_true(:,k),v_applied(k));


figure(1);
hold on;stairs(z_true(1,k),z_true(2,k),'k*');pause(0.05);
hold on;stairs(Zreach{2},'Color','lightblue');

figure(2);
stairs(k,v_applied(k),'o');pause(0.05);

end

figure(2);
hold on;
stairs(1:k,z_true(1,1:k),'b');
hold on;
stairs(1:k,z_true(2,1:k),'g');
hold on;
stairs(1:k,v_applied(1:k),'k')

%applied input actual
u_applied = -tan(x_true(2,1:end-1))+(1./a*cos(x_true(2,1:end-1))).*v_applied(1:end-1);
figure(3);
hold on;
stairs(1:k,x_true(1,1:k),'b');
hold on;
stairs(1:k,x_true(2,1:k),'g');
hold on;
stairs(1:k,u_applied(1:k),'k')


