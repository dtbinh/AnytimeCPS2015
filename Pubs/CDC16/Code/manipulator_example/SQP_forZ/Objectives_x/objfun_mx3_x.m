function f = objfun_mx3_x(x)
c1 = 10;
c2 = 1;
c3 = 1;
c4 = 1;
u_up = 10; 
u_low = -10;
%note, this guy is being minimized
f = -x(3); %highest x3
%f = +x(7)
%f = -(c1*(x(2)^2)*sin(x(1)) - (c1*cos(x(1))-c2)*(c1*sin(x(1))+c2*(x(1)-x(3))) ...
%            + c3*(x(1)-x(3)) );%+ c4*u_low);