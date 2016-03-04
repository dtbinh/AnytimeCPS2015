function [c, ceq] = confun_violator_x(x)
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
load('SetsAndParams_Z.mat');
Z = Zset;
temp = Z.A*x(5:8)-Z.b;

c = [%-X.A*x(1:4)+X.b+eps*ones(numel(X.b),1); %z not in Zset;
-sum(temp>0)+0.9;    
X_set_overbar.A*x(1:4)-X_set_overbar.b]; % x/inX_set_overbar

% Nonlinear equality constraints

%z = T(x)
ceq = [x(5)- x(1);...
    x(6)-x(2);...
    x(7)+params.c1*sin(x(1))+params.c2*(x(1)-x(3));...
    x(8)+params.c1*x(2)*cos(x(1))+params.c2*(x(2)-x(4))];