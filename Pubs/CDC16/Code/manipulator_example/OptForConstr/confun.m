function [c, ceq] = confun(x)
% Nonlinear inequality constraints
% c = [1.5 + x(1)*x(2) - x(1) - x(2);     
%      -x(1)*x(2) - 10;
%      x(1)-2; %bounds on x
%      -2-x(1);
%      x(2)-2;
%      -2-x(2)];
c = [x(1)-pi/2;
    -x(1)-pi/2;
    x(2)-pi/2;
    -x(2)-pi/2;
    x(3)-pi/4;
    -x(3)-pi/4;
    x(4)-pi/3;
    -x(4)-pi/3];
% Nonlinear equality constraints
ceq = [];