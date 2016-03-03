function [Zkp1,Xkp1] = getReachSetsViaZ(Zk,V,A_d,B_d,Z,X,Wproc,params)
%[Zkp1,Xkp1] = getReachSetsViaZ(Zk,V,A_d,B_d,Z,X,W,a)
Xsafe = X;
n = size(A_d,2);
X = std2aug(Zk.A,Zk.b);
U = std2aug(V.A,V.b);
W = std2aug(Wproc.A,Wproc.b);
E = eye(size(Wproc.A,2));

Zkp1aug = reach(A_d,B_d,E,X,U,W);
Zkp1 = Polyhedron('A',Zkp1aug(:,1:n),'b',Zkp1aug(:,n+1));
Zkp1 = intersect(Zkp1,Z);
Zkp1.minHRep;
Xkp1 = T_inv_diffeo(Zkp1,params);
Xkp1 = intersect(Xkp1,Xsafe);
Xkp1.minHRep;