function [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ(A,B,K_lqr,N,Z,V_inner_global,E_max,W)

%% standalone for testing
L_N = (A-B*K_lqr)^N;
What = W+E_max+(-A*E_max);
What.minHRep;
%note indexing starts from 1 and not 0 since fucking matlab is shite
Zsets{1} = Z - E_max;
Zsets{1}.minHRep; 
for i = 2:N+1
    Zsets{i} = Zsets{i-1}-((A-B*K_lqr)^(i-1))*E_max;
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
tmax = 200;
lambda = 1;
tol = .1;%[];

[Cdelta,tstar,fd] = kinfset(A,B,E,X,U,Wset,T,tmax,lambda,tol); %robust inv set
Cdelta_MPT = Polyhedron('A',Cdelta(:,1:size(A,2)),'b',Cdelta(:,size(A,2)+1:end));
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