function [Zkp1,Xkp1] = getReachSetsViaZ(Zk,V,A_d,B_d,Z,X,Wproc,params)
%[Zkp1,Xkp1] = getReachSetsViaZ(Zk,V,A_d,B_d,Z,X,W,a)
%% standalone
Xsafe = X; %this is now the initial set of x's, smaller than the real safe set
% n = size(A_d,2);
% X = std2aug(Zk.A,Zk.b);
% U = std2aug(V.A,V.b);
% W = std2aug(Wproc.A,Wproc.b);
% E = eye(size(Wproc.A,2));
% 
% Zkp1aug = reach(A_d,B_d,E,X,U,W); %how about MPT here?? man fuck this shit
% Zkp1 = Polyhedron('A',Zkp1aug(:,1:n),'b',Zkp1aug(:,n+1));
speedup = 1;
if(speedup)
[Zk,~,~] = getRect(Zk); %rectangles to speedup
end
sys = LTISystem('A',A_d,'B',B_d,'C',eye(size(A_d,2))); %using MPT
%'reaching'
Zkp1 = sys.reachableSet('X',Zk,'U',V);
Zkp1.minHRep;
%'add process noise'
Zkp1 = plus(Zkp1,Wproc,'fourier'); %add process noise to the set man
Zkp1 = intersect(Zkp1,Z);
%'minhrep'
%Zkp1.minHRep;
Xkp1 = T_inv_diffeo(Zkp1,params);
%'intersect'
%keyboard
Xkp1 = intersect(Xkp1,Xsafe);

Xkp1.minHRep;