function [A, B, C, D] = pendulum_on_cart_model

M = .5;
m = 0.2;
b = 0.1;
I = 0.006;
g = 9.8;
l = 0.3;

p = I*(M+m)+M*m*l^2; %denominator for the A and B matrices

A = [0      1              0           0;
     0 -(I+m*l^2)*b/p  (m^2*g*l^2)/p   0;
     0      0              0           1;
     0 -(m*l*b)/p       m*g*l*(M+m)/p  0];
B = [     0;
     (I+m*l^2)/p;
          0;
        m*l/p];
C = [1 0 0 0;
     0 0 1 0];
D = [0;
     0];
 
end
 
% states = {'x' 'x_dot' 'phi' 'phi_dot'};
% inputs = {'u'};
% outputs = {'x'; 'phi'};
% 
% sys_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);
% 
% Kcont=-lqr(sys_ss,eye(size(A,1)),eye(size(B,2)),zeros(size(A,1),size(B,2))); %continuous LQR design;
% 
% %discretize sys
% sys_d=c2d(sys_ss,0.01);
% K=-dlqr(sys_d.a,sys_d.b,eye(size(A,1)),eye(size(B,2)),zeros(size(A,1),size(B,2)));
