function [c, ceq] = confun2_unicycle(x,optParams)
%%
%x = [z;u]
%z+ = Az + bu

Nx = optParams.dim;
N = optParams.len;
Nu = optParams.dim_u;
h = optParams.h;

xx = zeros(Nx,N);
uu = zeros(Nu,N-1);
ceq_dyn = zeros(size(xx));

% initial condition
ceq_init  = x(1:Nx) - optParams.x0;


% dynamics;
u_temp = x(Nx*N+1:end);
x_temp = x(1:Nx*N);
xx = reshape(x_temp,Nx,N);
uu = reshape(u_temp,Nu,N-1);

for t = 2:N
    ceq_dyn(1,t) = xx(1,t) - (xx(1,t-1) + h*uu(1,t-1)*cos(xx(3,t-1)));
    ceq_dyn(2,t) = xx(2,t) - (xx(2,t-1) + h*uu(1,t-1)*sin(xx(3,t-1)));
    ceq_dyn(3,t) = xx(3,t) - (xx(3,t-1) + h*uu(2,t-1));
end


% state feasibility
A_big_x = kron(eye(N),optParams.P_feas.A);
B_big_x = repmat(optParams.P_feas.b,N,1);
c_state = A_big_x*x(1:Nx*N) - B_big_x; 

% input feasibility
A_big_u = kron(eye(N-1),optParams.U_feas.A);
B_big_u = repmat(optParams.U_feas.b,N-1,1);
c_input = A_big_u*x(Nx*N+1:end) - B_big_u;

% terminal set
%c_term = optParams.P_final.A*x(N*Nx-Nx+1:N*Nx)-optParams.P_final.b;
c_term = [];
if(optParams.robConstr)
    rho = [];
c = [c_state;c_input;c_term;-rho];
else
c = [c_state;c_input;c_term]; 
end

ceq = [ceq_init;ceq_dyn(:)];
