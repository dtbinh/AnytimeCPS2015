


% Params
g = 9.8;
m = 0.5;
h = 1/100;
% continuous


A = [zeros(1,3) 1 0 0;...
    zeros(1,4) 1 0;
    zeros(1,5) 1;
    zeros(3,6)];
B = [zeros(3,3);diag([g -g 1/m])];
C = eye(6);
D = zeros(6,3);

%discrete
sys_c = ss(A,B,C,D);

sys_d = c2d(sys_c,h);

