function [Zkp1,Xkp1] = getReachSetsViaZ(Zk,V_outer_global,A_d,B_d,Z,X,a)

Xsafe = X;
n = size(A_d,2);
X = std2aug(Zk.A,Zk.b);
U = std2aug(V_outer_global.A,V_outer_global.b);
W = [];
E = zeros(2,1);

Zkp1aug = reach(A_d,B_d,E,X,U,W);
Zkp1 = Polyhedron('A',Zkp1aug(:,1:n),'b',Zkp1aug(:,n+1));
Zkp1 = intersect(Zkp1,Z);
Zkp1.minHRep;
Xkp1 = T_inv_diffeo(Zkp1,a);
Xkp1 = intersect(Xkp1,Xsafe);
Xkp1.minHRep;
