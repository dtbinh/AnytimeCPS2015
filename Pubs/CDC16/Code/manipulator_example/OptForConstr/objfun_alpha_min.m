function f = objfun_alpha_min(x)
load('SetsAndParams.mat');

c1 = params.c1;
c2 = params.c2;
c3 = params.c3;
c4 = params.c4;
c5 = params.c5;


%alpha
f = (c1*(x(2)^2)*sin(x(1)) - (c1*cos(x(1))-c2)*(c1*sin(x(1))+c2*(x(1)-x(3))) ...
            + c3*(x(1)-x(3)) );%+ c4*u_low);