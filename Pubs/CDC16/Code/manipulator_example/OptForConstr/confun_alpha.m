function [c, ceq] = confun_alpha(x)
% Nonlinear inequality constraints
% c = [1.5 + x(1)*x(2) - x(1) - x(2);     
%      -x(1)*x(2) - 10;
%      x(1)-2; %bounds on x
%      -2-x(1);
%      x(2)-2;
%      -2-x(2)];
load('SetsAndParams.mat');
X = Xreach;
c = X.A*x-X.b;
% Nonlinear equality constraints
ceq = [];