function Zj = getZjs(xk,Z,E,W,Xk,a,N)

F = eye(size(Z.A,2));
Zj = cell(1+HorizonLength,1);

E_tilde{1} = get_E_tilde_bound(xk,a,Xk,E);

Zj{1} = Z-F*E_tilde{1};

for j = 2:N+1
    
end


