function [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W)
%function [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W)
%% standalone for testing
L_N = (A_d-B_d*K_lqr_d)^N;
%fucking plus doesn't like to work, so do this
temp = plus(W,E_max,'fourier');
What = plus(temp,-A_d*E_max,'fourier');
%What = W+E_max+(-A_d*E_max);
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

E = L_N;
%X = std2aug(Z.A,Z.b);
U = std2aug(V_inner_global.A,V_inner_global.b);
Wset = std2aug(What.A,What.b);
T = std2aug(Zsets{N+1}.A,Zsets{N+1}.b); %Omega=Z_N
X = T;
tmax = 10000; %>21 works
lambda = 0.9995;%.999995;%0.991 works, 0.999995
tol = .01; %.0001 works


%% 
[Cdelta,tstar,fd] = kinfset(A_d,B_d,E,X,U,Wset,T,tmax,lambda,tol); %robust inv set
Cdelta_MPT = Polyhedron('A',Cdelta(:,1:size(A_d,2)),'b',Cdelta(:,size(A_d,2)+1:end));
Z_f_worst = Cdelta_MPT - L_N*What;
status = fd*(~Zsets{N+1}.isEmptySet)*(~Cdelta_MPT.isEmptySet)*(~Z_f_worst.isEmptySet);
if(status~=1)
   if(Zsets{N+1}.isEmptySet)
      'Z_N is empty' 
   end
   if(fd~=1)
      'Term set fucked up' 
   end
end
Z_f_worst = intersect(Z_f_worst,Zsets{N+1});
Cdelta_MPT = intersect(Cdelta_MPT,Zsets{N+1});