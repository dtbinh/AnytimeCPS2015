function Zj = getZjs(xk,X,Z,E,W,X_k,U,V_inner_global,A_d,B_d,K_lqr_d,a,N)
%%
F = eye(size(Z.A,2));
Zjk = cell(1+N,1);

E_tilde{1} = get_E_tilde_bound(xk,a,X_k,E);
X_reach{1} = X_k;
Z_reach{1} = T_diffeo(X_k,a);
Z_reach{1} = intersect(Z,Z_reach{1});
Z_reach{1}.minHRep;

Zjk{1} = Z-F*E_tilde{1};
Z_k = [];
L{1} = eye(size(A_d,2));
[E_tilde,Z_reach,X_reach,V_inner_local] = getAllErrorSets(xk,X_k,Z_k,X,Z,E,W,U,V_inner_global,A_d,B_d,a,N);

for j = 2:N+1
    L{j} = (A_d-B_d*K_lqr_d)*L{j-1};
    What = W + E_tilde{j} + (-A_d*E_tilde{j-1});
    %What = W + E_max + (-A_d*E_max);
    Zjk{j} = Zjk{j-1}-L{j}*What;
    
end


