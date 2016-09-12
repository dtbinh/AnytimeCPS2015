a1 = 2*pi/3;
a2 = 4/3;
a3 = 4*pi/3;
a4 = pi;
a5 = 16*pi/9;

%syms t a1 a2 a3 a4 a5;
syms t;
f = (sin(a1*t) + a2*t*cos(a3*t));
g = (a4*t-a5*t^3);
phi = f/g;

dphi_by_dt_1 = (diff(f,t)*g - diff(g,t)*f)/(g^2);
f1 = (diff(f,t)*g - diff(g,t)*f);
g1 = g^2;

dphi_by_dt_2 = diff(phi,t);
