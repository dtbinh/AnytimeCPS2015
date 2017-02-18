function [r_P,r_P_der] = robustness_CaseStudy_u(X,optParams)
% robustness for CaseStudy
%Phi = eventually(p_1 in Tset) AND eventually(p_2 in Tset) AND always( not(p_1 in
% Z_1) OR (z_1 in Rule1)) AND always( not(p_2 in Z_1) OR (z_2 in Rule1)) AND
% always( not(p_1 in Z_2) OR (z_1 in Rule2)) AND always( not(p_2 in Z_2) OR (z_2 in Rule2))
% AND always(not(p_1 in NoFly)) AND always(not(p_2 in NoFly)) AND
% always( norm(p_1-p_2)^2 <= dmin^2)

%trajectory Sx (n*N) (n = sys dim, N = steps)
%%
r_P_der = [];
r_phi = zeros(9,1);

Nx = optParams.dim_x;
Nu = optParams.dim_u;
N = optParams.len;

state_1 = reshape(X(1:Nx*N),Nx,N);
state_2 = reshape(X(Nx*N+1:end),Nx,N);

pos_1 = state_1(4:6,:);
pos_2 = state_2(4:6,:);
%%
r_phi(1) = robustness_eventually_P(pos_1,optParams.wavparams.Terminal,0);
r_phi(2) = robustness_eventually_P(pos_2,optParams.wavparams.Terminal,0);
r_phi(7) = robustness_always_notP(pos_1,optParams.wavparams.NoFly,0);
r_phi(8) = robustness_always_notP(pos_2,optParams.wavparams.NoFly,0);

r_phi(9) = robustness_always_SafeDist([pos_1;pos_2],optParams.d_min,0);

r_phi(3) = robustness_always_IfAthenB(pos_1,optParams.wavparams.Zone1, ...
    optParams.wavparams.Zone1_rules,0);
r_phi(4) = robustness_always_IfAthenB(pos_2,optParams.wavparams.Zone1, ...
    optParams.wavparams.Zone1_rules,0);
r_phi(5) = robustness_always_IfAthenB(pos_1,optParams.wavparams.Zone2, ...
    optParams.wavparams.Zone2_rules,0);
r_phi(6) = robustness_always_IfAthenB(pos_2,optParams.wavparams.Zone2, ...
    optParams.wavparams.Zone2_rules,0);


r_P = SoftMin(r_phi);