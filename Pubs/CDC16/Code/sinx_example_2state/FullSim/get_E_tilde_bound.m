function Etilde_k = get_E_tilde_bound(xk,a,Xk,E)
%%
[~,maxs,mins] = getRect(Xk);
%[~,maxe,mine] = getRect(E);
%after lin: T(x+e) = T(x) + M(x)e = T(x) + e_tilde
if(mx(2)>=0 && mn(2)<=0) % is zero in this interval?
    %yes
    scaleE2 = a*cos(0);
else
    %no
    scaleE2 = a*cos(min(abs(maxs(2)),abs(mins(2))));
end
M_max = [1 0; 0 scaleE2];
Etilde_k = M_max*E;
Etilde_k.minHRep;
