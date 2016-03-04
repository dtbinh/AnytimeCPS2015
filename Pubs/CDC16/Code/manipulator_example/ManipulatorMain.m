%constants
m = 1/9.8; %to make life easy, all constants  = 1;
k = 1;
I = 1;
J = 1;
L = 1;
g = 9.8;
c1 = m*g*L/I;
c2 = k/I;
c3 = k^2/(I*J);
c4 = k/(I*J);
c5 = k/J;
params.c1 = c1;
params.c2 = c2;
params.c3 = c3;
params.c4 = c4;
params.c5 = c5;

%states and intervals
x1_max = pi;%pi/4;
x1_min = -pi;%-pi;%-pi/4;
x2_max = pi;%pi;%pi/4;
x2_min =  -pi;%-pi;%-pi/4;
x3_max = 2*pi;%pi;%2*pi;
x3_min = -2*pi;%-pi;%-2*pi;
x4_max = 2*pi;%pi;%2*pi;
x4_min = -2*pi;%-pi;%-2*pi;

X = Polyhedron('lb',[x1_min;x2_min;x3_min;x4_min],'ub',[x1_max;x2_max;x3_max;x4_max]);
X.minHRep; %min rep that shi, G

x1 = interval(x1_min,x1_max);
x2 = interval(x2_min,x2_max);
x3 = interval(x3_min,x3_max);
x4 = interval(x4_min,x4_max);
% input interval
u_max = 10;
u_min = -10;
U = Polyhedron('lb',u_min,'ub',u_max);
U.minHRep;
u = interval(u_min,u_max);

%feedback linearization stuff
% u = (1/beta)*v - alpha/beta;
alpha_fb = c1*(x2^2)*sin(x1) - (c1*cos(x1)-c2)*(c1*sin(x1)+c2*(x1-x3)) + c3*(x1-x3);
gamma_fb = c4;

%after fb lin
A_manip = [0 1 0 0;0 0 1 0;0 0 0 1;0 0 0 0];
B_manip = [0;0;0;1];
K_manip = lqr(A_manip,B_manip,eye(4),1*eye(1),[]);

% init states
x1_m_0 = -pi/10;
x2_m_0 = 0;
x3_m_0 = +pi/10;
x4_m_0 = 0;

% Error set
mag = deg2rad(1);
E = Polyhedron('lb',-mag*ones(4,1),'ub',mag*ones(4,1));

% Disturbance set
dmag = 10^-10;
W = Polyhedron('lb',-dmag*ones(4,1),'ub',dmag*ones(4,1));
%% get actual admissible region for X and safe Z
mainOpt
%% init this file, get worst case sets
info = 'file for optimization params';
Xreach = X_set_final; %this is the real admissible set for x0's
Z = Z_set_final;
save('SetsAndParams.mat','params','Xreach','info');

%get republican sets
V_inner_global = getLocalVInner_interval(Xreach,U,params);
E_max = get_E_tilde_bound(Xreach,E,params);

%% discretization and term set
N = 5;
h = 1/10;
sys = ss(A_manip,B_manip,eye(4),zeros(size(A_manip,2),size(B_manip,2)));
sys_d = c2d(sys,h);

Q = eye(size(A_manip,2));
R = eye(size(B_manip,2));
[K_lqr_d,~,~] = dlqr(sys_d.A,sys_d.B,Q,R,[]);
A_d = sys_d.A;
B_d = sys_d.B;

%fuck it go with the flow
[Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W);

%plot that garbage
figure(1);
plot(Z.projection(1:2));
hold on
plot(Cdelta_MPT.projection(1:2),'Color','yellow');
hold on;
plot(Z_f_worst.projection(1:2),'Color','blue');
xlabel('z_1');ylabel('z_2');

figure(2);
plot(Z.projection(3:4));
hold on
plot(Cdelta_MPT.projection(3:4),'Color','yellow');
hold on;
plot(Z_f_worst.projection(3:4),'Color','blue');
xlabel('z_3');ylabel('z_4');
