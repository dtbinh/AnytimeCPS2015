function [ZA Zb] = getZj_MPT(A,Acl,B_lift,Kx,Fhat,S,H,j,eps_k,eps)

% error sets
temp.A = [eye(size(A,1));-eye(size(A,1))];
E_k.b = eps_k*[ones(size(A,1),1);ones(size(A,1),1)];
E_k.A = temp.A;
E.b = eps*[ones(size(A,1),1);ones(size(A,1),1)];
E.A = temp.A;
Ek = Polyhedron('A',E_k.A,'B',E_k.b);
E = Polyhedron('A',E.A,'B',E.b);
What = plus(A*Ek,-E);
% if j = 0
if(j == 0)
    Z = minus(S,Fhat*Ek);
    Z.minHRep;
else
    for k = 0:j
        if(k==0)
            Z_ = minus(S,Fhat*E);
            Z_.minHRep;
            L_ = eye(size(B_lift,1),size(B_lift,1));
        else
            Z = minus(Z_,L_*Fhat*What);
            Z.minHRep;
            Z_ = Z;
            L_ = Acl*L_;
        end
    end
end

%Return
ZA = Z.A;
Zb = Z.b;
