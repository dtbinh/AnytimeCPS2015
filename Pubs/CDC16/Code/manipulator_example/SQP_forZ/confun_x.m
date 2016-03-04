function [c, ceq] = confun_x(x)
load('SetsAndParams_Z.mat');
% Nonlinear inequality constraints
Z = Z_set_overbar;
%z in Z
c = Z.A*x(5:8)-Z.b; %x is first 4, z is next 4

% Nonlinear equality constraints
%x = Tinv(z);
ceq = [x(5) - x(1);
    x(6) - x(2);
    %x(7) + 1*sin(x(1)) + 1*(x(1)-x(3));
    %x(8) + 1*x(2)*cos(x(1)) + 1*(x(2)-x(4))];
    x(3)-(1/1)*(x(7)+1*sin(x(5))+1*x(5));
    x(4)-(1/1)*(x(8)+1*x(6)*cos(x(5))+1*x(6))];