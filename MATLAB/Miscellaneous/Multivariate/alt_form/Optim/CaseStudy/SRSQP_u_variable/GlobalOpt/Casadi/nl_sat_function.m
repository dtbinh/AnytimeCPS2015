function gout = nl_sat_function(w, obs, goal, optParams, U_intersect)

%gout = U_intersect.A*u;
[~,ceq] = confun_SingleQuad_case_Casadi(w,optParams.x0,optParams);
if(optParams.maxim)
gout = ceq; 
else
gout = [ceq;getRobustness_u_quad_Casadi_full(w, obs, goal, optParams)];
end