%constants
m = 1;
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

%states and intervals
x1_max = pi;
x1_min = -pi;
x2_max = pi;
x2_min = -pi;
x3_max = pi/4;
x3_min = -pi/4;
x4_max = pi/4;
x4_min = -pi/4;

x1 = interval(x1_min,x1_max);
x2 = interval(x2_min,x2_max);
x3 = interval(x3_min,x3_max);
x4 = interval(x4_min,x4_max);
% input interval
u_max =30;
u_min = -30;
u = interval(u_min,u_max);

%feedback linearization stuff
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