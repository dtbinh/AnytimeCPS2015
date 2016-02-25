function Zj = getZjs(xk,Z,E,W,Xk,a,HorizonLength)

F = eye(size(Z.A,2));
Zj = cell(1+HorizonLength,1);
N = HorizonLength;

E_tilde{1} = get_E_tilde_bound(xk,a,Xk,E);

Zj{1} = Z-F*

for j = 2:HorizonLength+1
    
end


