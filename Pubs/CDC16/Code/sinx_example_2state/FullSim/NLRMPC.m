function [z,v] = NLRMPC(z0_hat,Zjk,Z_f_worst,V_in,A_d,B_d,N)
%function [z,v] = NLRMPC(z0_hat,Zjk,V_in,A_d,B_d)
% Q = eye(2);
% R = eye(1);
cvx_clear
cvx_begin
cvx_solver gurobi
variable z(2,N+2)
variable v(1,N+1)
minimize sum(sum(abs(z)))+0.1*sum(sum(abs(v))) %1-norm min%converges for 0.0001
subject to
z(:,1) == z0_hat;
for j = 1:N+1
    z(:,j+1) == A_d*z(:,j) + B_d*v(:,j); %dynamics
    Zjk{j}.A*z(:,j)<=Zjk{j}.b; %safe state
    V_in{j}.A*v(:,j)<=V_in{j}.b; %input limits
end
Z_f_worst.A*z(:,N+2)<=Z_f_worst.b; %Terminal
cvx_end
