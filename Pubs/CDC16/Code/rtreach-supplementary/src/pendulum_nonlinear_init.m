%physical parameters

syms Va x v theta omega;

syms A_x A_theta;
syms B_x C_x B_theta C_theta;

syms g m Ki Kb Kg r Ra Bm Btheta M Jm l;

% symbolic v_dot and omega_dot for paper...
syms fc fp D C1 C2;
syms Mbar;
v_dot = (1/D) * ( (1/3) * m * l^2 * (- fc - C1) + (1/2)*m*l*cos(theta)*(fp+C2) ) 
latex(v_dot)
omega_dot = (1/D)*( (-1/2)*m*l*cos(theta)*(- fc - C1) - Mbar * (fp + C2) ) 
latex(omega_dot)

Bbar=((Kg*Bm)/(r^2))+(((Kg^2)*Ki*Kb)/((r^2)*Ra));
Bl=((Kg*Ki)/(r*Ra));

Mbar=m+M+(Kg*Jm)/(r^2); %effective mass
Dl=(4*Mbar)-3*m;

fc = sign(v) * A_x * exp(-C_x * abs(v)) + B_x * v;
fp = sign(omega) * A_theta * exp(-C_theta * abs(omega)) + B_theta * omega;

D = (1/3) * Mbar * m * l^2 - (1/4)*m^2*l^2*cos(theta)^2;

C1 = Bbar * v - (1/2)*m*l*sin(theta)*omega^2;
C2 = (-1/2)*m*g*l*sin(theta);

latex(fc)
latex(fp)
latex(D)
latex(C1)
latex(C2)
return;

% Va = u = Kx
% Va = Kx: control input
state_vector = [x; theta; v; omega]; % double check order

K=[7.6, 42.85, 13.54, 8.25];     %safety, from Ks

b2=1.94; b4=4.44; %real matrix
B=[0; b2; 0; -b4];

Va = B*K*state_vector;
%Va = K*state_vector;

x_dot = v
%v_dot = (1/D) * ( (1/3) * m * l^2 * (Bl * (Va(2)) - fc - C1) + (1/2)*m*l*cos(theta)*(fp+C2) )
% factor out Va: use it as additive control for Va = Kx, where here we just drop it
% and use B*K*x, where B has incorporated all the coefficients
v_dot = (1/D) * ( (1/3) * m * l^2 * (- fc - C1) + (1/2)*m*l*cos(theta)*(fp+C2) ) 
v_dot = simplify(v_dot,'Steps',100)

%v_dot = v_dot + Va(2); % with control

theta_dot = omega
%omega_dot = (1/D)*( (-1/2)*m*l*cos(theta)*(Bl*(Va(4)) - fc - C1) - Mbar * (fp + C2) )
% factor out Va:
omega_dot = (1/D)*( (-1/2)*m*l*cos(theta)*(- fc - C1) - Mbar * (fp + C2) ) 
omega_dot = simplify(omega_dot,'Steps',100)

%omega_dot = omega_dot + Va(4); % with control

% 0 static friction 
A_x = 0;
A_theta = 0;

% ignore other frictions
B_x = 0.01;
C_x = 0.01;
B_theta = 0.0001;
C_theta = 0.0001;

g=-9.8; %gravity: -9.8 m/s
m=1;    %mass
Ki=0.9; %torque constant
Kb=0.9; %back-emf constant
Kg=1;   %gear ratio
r=2; %
Ra=0.95;    %armature resistance
Bm=1.95;    %
Btheta=0.95;    
M=5;    %mass
Jm=5;   %moment of inertia
l=0.5;  %length

eval(v_dot)

eval(omega_dot)

% equation for plugged in values
vpa(eval(v_dot))

vpa(eval(omega_dot))