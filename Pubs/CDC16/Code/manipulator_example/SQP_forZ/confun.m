function [c, ceq] = confun(x)
load('SetsAndParams_Z.mat');
% Nonlinear inequality constraints

%Hx<=g, i.e. x\inX
c = X.A*x(1:4)-X.b; %x is first 4, z is next 4

% Nonlinear equality constraints
%z = T(x)
ceq = [x(5)- x(1);...
    x(6)-x(2);...
    x(7)+params.c1*sin(x(1))+params.c2*(x(1)-x(3));...
    x(8)+params.c1*x(2)*cos(x(1))+params.c2*(x(2)-x(4))];