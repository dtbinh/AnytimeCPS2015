function [c, ceq] = confun_violator(x)
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

temp = X.A*x(1:4)-X.b;

c = [%-X.A*x(1:4)+X.b+eps*ones(numel(X.b),1); %x not in X
-sum(temp>0)+0.9;    
Z_set_overbar.A*x(5:8)-Z_set_overbar.b]; % z/inZ

% Nonlinear equality constraints
%x = Tinv(z)
%ceq = x(1)-sin(x(2));
ceq = [x(5) - x(1);
    x(6) - x(2);
    %x(7) + 1*sin(x(1)) + 1*(x(1)-x(3));
    %x(8) + 1*x(2)*cos(x(1)) + 1*(x(2)-x(4))];
    x(3)-(1/1)*(x(7)+1*sin(x(5))+1*x(5));
    x(4)-(1/1)*(x(8)+1*x(6)*cos(x(5))+1*x(6))];