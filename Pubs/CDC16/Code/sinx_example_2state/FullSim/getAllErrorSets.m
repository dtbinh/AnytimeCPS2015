function [E_tilde_jgk,Z_k_reach,X_k_reach] = getAllErrorSets(x_k,X_k,Z_k,X,Z,E,V_outer_global,A_d,B_d,a,N)
%get all error sets till horizon from starting set X_k

X_k_reach{1} = X_k;
Z_k_reach{1} = T_diffeo(X_k_reach{1},a);
Z_k_reach{1} = intersect(Z_k_reach{1},Z);
Z_k_reach{1}.minHRep;
for j = 2:N
    [Z_k_reach{j},X_k_reach{j}] = getReachSetsViaZ(Z_k_reach{j-1},V_outer_global,A_d,B_d,Z,X,a);
    if(Z_k_reach{j}.isEmptySet|| X_k_reach{j}.isEmptySet)
       'Some reach set does not intersect with safe set'
       pause;
    end
end

if(0) %plot if you feel like it
    for j = 1:15
        hold on
        Z_k_reach{j}.plot('Color','green');pause;
    end
end

%%
for j = 1:N
   E_tilde_jgk{j} = get_E_tilde_bound([],a,X_k_reach{j},E);
end