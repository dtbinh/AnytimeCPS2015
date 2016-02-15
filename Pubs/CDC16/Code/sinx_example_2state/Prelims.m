% For the plant given by 
% dx1/dt = a*sin(x2)
% dx2/dt = -x1^2 + u
% for the feedback lin, note, y=h(x)=x1
% system has relative degree 2 in the domain x|cos(x2)~=0
% alpha(x) = tan(x2)
% beta(x) = a*cos(x2)
% u = alpha(x) + (1/beta(x))*v
%% linearized dynamics
% z = T(x) = [x1;a*sin(x2)];
A=[0 1;0 0];
B=[0; 1];
C=eye(2);
Q = eye(size(A,2));
R = eye(size(B,2));
K_lqr = lqr(A,B,Q,R,[]);

%% nl model param and init states
x1_0 = pi/2;
x2_0 = pi/4;
a = 1;
%% set limits
% states
x1_min = -pi;
x1_max = +pi;
x2_min = -pi/3;
x2_max = +pi/3;
X = Polyhedron('lb',[x1_min;x2_min],'ub',[x1_max;x2_max]);

% error
e1_min = -pi/180;
e1_max = +pi/180;
e2_min = -pi/180;
e2_max = +pi/180;
E = Polyhedron('lb',[e1_min;e2_min],'ub',[e1_max;e2_max]);

% disturbance in state (xkp1 = Axk + bk + wk)
w1_min = -(pi/180)*10^(-3);
w1_max = +(pi/180)*10^(-3);
w2_min = -(pi/180)*10^(-3);
w2_max = +(pi/180)*10^(-3);
W = Polyhedron('lb',[w1_min;w2_min],'ub',[w1_max;w2_max]);

% input
u_min = -1.2;
u_max = 1.2;
U = Polyhedron('lb',u_min,'ub',u_max);

% after state transform Z = T(X)
% z1 = x1 \in [x1_min, x2_max]
% z2 = a*sin(x2) \in [a_sin(x2_min),a_sin(x2_max)] since x2 domain is nice

% state limits Z for state after fb linearization
z1_min = x1_min;
z1_max = x1_max;
z2_min = a*sin(x2_min);
z2_max = a*sin(x2_max);
Z = Polyhedron('lb',[z1_min;z2_min],'ub',[z1_max;z2_max]);


%% run simlunk mdl
sim('asinx2model');

