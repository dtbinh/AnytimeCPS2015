function V_outer_local = getLocalVOuter(x_k,X_k,Z_k,Z,X,U,a)
if(~isempty(Z_k))
   Z_k = intersect(Z_k,Z); 
end

if(isempty(X_k))
    X_k = T_inv_diffeo(Z_k,a);
    X_k = intersect(X_k,X);
    X_k.minHRep;
end


save('Data/vlims_data.mat','X_k','U','a');
xinit = [x_k;1];
options = optimset('Algorithm','sqp');
[x_min,fval_min] = ... 
fmincon(@v_lims_min,xinit,[],[],[],[],[],[],@v_lims_constraint,options);

[x_max,fval_max] = ... 
fmincon(@v_lims_max,xinit,[],[],[],[],[],[],@v_lims_constraint,options);

V_outer_local = Polyhedron('lb',fval_min,'ub',-fval_max);
V_outer_local.minHRep;
%compare to line search
