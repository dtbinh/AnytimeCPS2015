function [c, ceq] = confun(x)
% Nonlinear inequality constraints
% c = [1.5 + x(1)*x(2) - x(1) - x(2);     
%      -x(1)*x(2) - 10;
%      x(1)-2; %bounds on x
%      -2-x(1);
%      x(2)-2;
%      -2-x(2)];
% c = [x(1)-pi/2;
%     -x(1)-pi/2;
%     x(2)-pi/2;
%     -x(2)-pi/2;
%     x(3)-pi/4;
%     -x(3)-pi/4;
%     x(4)-pi/3;
%     -x(4)-pi/3];
load('SetsAndParams.mat');
c = X.A*x(1:4)-X.b; %x is first 4, z is next 4

% Nonlinear equality constraints
%ceq = x(1)-sin(x(2));
ceq = [x(5) - x(1);
    x(6) - x(2);
    x(7) + 1*sin(x(1)) + 1*(x(1)-x(3));
    x(8) + 1*x(2)*cos(x(1)) + 1*(x(2)-x(4))];