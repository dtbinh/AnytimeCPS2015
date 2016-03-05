function [z,v,optval] = NLRMPC(z0_hat,Zjk,Z_f_worst,V_in,A_d,B_d,N,Q,Q_term,R)
%function [z,v,optval] = NLRMPC(z0_hat,Zjk,Z_f_worst,V_in,A_d,B_d,N,Q,Q_term,R)
% Q = eye(2);
% R = eye(1);
%%
n = size(A_d,2);
m = size(B_d,2);
cvx_clear
cvx_begin
cvx_solver gurobi
variable z(n,N+2)
variable v(m,N+1)
%minimize sum(sum(abs(z)))+0.1*sum(sum(abs(v))) %1-norm min%converges for 0.0001 ...
                                                %questionable for 0.1
%Q,R,Q_term min
minimize quad_form(z(:,1),Q) + quad_form(z(:,2),Q) + quad_form(z(:,3),Q) + ...
    quad_form(z(:,4),Q) + quad_form(z(:,5),Q) + quad_form(z(:,6),Q) + ...
    quad_form(z(:,7),Q_term) + ...
    quad_form(v(:,1),R) + quad_form(v(:,2),R) + quad_form(v(:,3),R) + ...
    quad_form(v(:,4),R) + quad_form(v(:,5),R) + quad_form(v(:,6),R)
    %z'Q'z + v'Rv + z_f'Q_fz'f, for N = 5
                                                
subject to
z(:,1) == z0_hat;
for j = 1:N+1
    z(:,j+1) == A_d*z(:,j) + B_d*v(:,j); %dynamics
    Zjk{j}.A*z(:,j)<=Zjk{j}.b; %safe state
    V_in{j}.A*v(:,j)<=V_in{j}.b; %input limits
end
Z_f_worst.A*z(:,N+2)<=Z_f_worst.b; %Terminal
cvx_end
optval = cvx_optval;