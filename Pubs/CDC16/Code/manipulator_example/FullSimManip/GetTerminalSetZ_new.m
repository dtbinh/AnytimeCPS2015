function [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ_new(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W)
%function [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ_new(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W)

%%
L_N = (A_d-B_d*K_lqr_d)^N;
temp = plus(W,E_max,'fourier');
What = plus(temp,-A_d*E_max,'fourier');
What.minHRep;
%note indexing starts from 1 and not 0 since fucking matlab is shite
Zsets{1} = Z - E_max;
Zsets{1}.minHRep; 
for i = 2:N+1
    Zsets{i} = Zsets{i-1}-((A_d-B_d*K_lqr_d)^(i-1))*What;
    Zsets{i}.minHRep;
    if(Zsets{i}.isEmptySet)
       'empty Z_i at'
       i
    end
end
ZN_mpt = Zsets{N+1};
ZN = poly2struct(ZN_mpt);
[~,wmx,wmn] = getRect(W);
[~,emx,emn] = getRect(E_max);
wmax = max(wmx);
emax = max(emx);
sys.A = A_d;
sys.B = B_d;
%%
[Cinv, status] = calcInvSet_new( sys, ZN, L_N, wmax, emax, inf, inf, 1000, 1);
Cdelta_MPT = Polyhedron(Cinv.H,Cinv.K);
Z_f_worst = Cdelta_MPT - L_N*What;
Z_f_worst = intersect(Z_f_worst,Zsets{N+1});
Cdelta_MPT = intersect(Cdelta_MPT,Zsets{N+1});
