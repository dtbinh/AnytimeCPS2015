%Sim Main
'Preliminaries'
ManipulatorMain;

%%
Z = Z_set_final;
X0 = X_set_final;
'Initializing plant'
%init state for linearized system
x_0 = [0.5;-0.25;0;0];

if(~X0.isInside(x_0))
   'Init State outside admissible region'
   keyboard;
end
z0 = T_diffeo(x_0,params);
x0 = T_inv_diffeo(z0,params);
if(x0~=x_0) %sanity check
    'Something is off'
end
%init estimate of x0
x0_hat = x0 + (mag)*(pi/180)*rand(numel(x0),1); %x0_hat = x0 + e0
%z0_hat = T_diffeo(x0_hat,params);
%get reach set for x0 with error in there
X_0 = plus(x0_hat,-E);
X_0.minHRep;

%% get term cost
'Computing term cost'
Q = eye(size(A_d,4));
%Q = [1 0 0 0;0 1 0 0;0 0 0.1 0;0 0 0 0.1];
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
V_inner_k = cell(Tsim,1); %local inner constraint set for v at time k
E_tilde_k = cell(Tsim,1); %error set for zhat at time k
figure(1);
plot(Z.projection(1:2));
hold on;
figure(2);
hold on;
pause(0.01);

for k = 1:Tsim-1
k
%measure plant
'Get measurements'
x_true(:,k) = T_inv_diffeo(z_true(:,k),params); %from lin dynamics
x_hat(:,k) = x_true(:,k) + (mag)*rand(numel(x0),1);    %add estimation error in x, xhat=x+e
z_hat(:,k) = T_diffeo(x_hat(:,k),params); %into z_hat
X_k = plus(x_hat(:,k),-E); %setin which it true state lies given that measurement

%get constraints
'Get constraints'
[Zjk,V_in,Zreach,Xreach,E_tilde] = getZjs(x_hat(:,k),X_k,X,Z,E,W,U,V_inner_global,A_d,B_d,K_lqr_d,params,N);
V_inner_k{k} = V_in{1};
E_tilde_k{k} = E_tilde{1};
%get zhat with these error chars
%z_hat(:,k) = plus(z_true(:,k),-E_tilde{1});
%solve mpc
'Solve MPC'
[z_pred,v_pred,optval(k)] = NLRMPC(z_hat(:,k),Zjk,Z_f_worst,V_in,A_d,B_d,N,Q,Q_term,R);
v_applied(k) = v_pred(1); %apply first input

%apply input to plant, update state
'Apply to plant'
z_true(:,k+1) = linplant(A_d,B_d,z_true(:,k),v_applied(k));


figure(1);
hold on;stairs(z_true(1,k),z_true(2,k),'k*');pause(0.05);
hold on;plot(Zreach{2}.projection(1:2),'Color','lightblue');

figure(2);
stairs(k,v_applied(k),'o');pause(0.01);
[~,mxv,mnv] = getRect(V_in{1});
hold on
plot(k,mxv,'k*');
hold on;
plot(k,mnv,'k*');
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
hold on
plot(1:k,u_max*ones(k,1),'.');
hold on
plot(1:k,u_min*ones(k,1),'.');

%% more plotting shite
figure;
hold on;
plot(1:k,v_applied(1:k));
hold all;
mxv = zeros(k,1);
mnv = zeros(k,1);
for i = 1:k
   [~,mxv(i),mnv(i)] = getRect(V_inner_k{i});
end
hold all;
plot(1:k,mxv,'-.');
hold all
plot(1:k,mnv,'-.');
hold all;
[~,mxv_g,mnv_g] = getRect(V_inner_global);
plot(1:k,mxv_g*ones(k,1),'--');
hold all;
plot(1:k,mnv_g*ones(k,1),'--');
legend('v','v_{max-online}','v_{min-online}','v_{max-global}','v_{min-global}');
grid on;