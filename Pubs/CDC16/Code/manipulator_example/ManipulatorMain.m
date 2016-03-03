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
x1_max = pi/4;%pi;%pi/4;
x1_min = -pi/4;%-pi;%-pi/4;
x2_max = pi/4;%pi;%pi/4;
x2_min = -pi/4;% -pi;%-pi/4;
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
u_max = 20;
u_min = -20;
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
x1_m_0 = -pi/4;
x2_m_0 = 0;
x3_m_0 = +pi/4;
x4_m_0 = 0;

%% init this file
info = 'file for optimization params';
Xreach = X;
save('SetsAndParams.mat','params','Xreach','info');