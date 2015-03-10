function [Cdelta]=getTermSetCdelta_invset(A,Acl,F,A_lift,B_lift,K,Kx,Dset,InputSet,LiftStateSet,Horizon)


% compute terminal set

Ln=(A_lift+B_lift*K)^(Horizon);

A_state = LiftStateSet.A;
b_state = LiftStateSet.b;
A_input = InputSet.A;
b_input = InputSet.b;


Wset=-Dset+A*Dset;

A_dist = Wset.A;
b_dist = Wset.b;

N=Horizon;
% Y_N=(Acl^(N-1))*F*A*Dset;

temp1=(Acl^(N-1))*F*A*Dset;

for i=2:N
    i
   temp = -(Acl)^(N-i)*B_lift*Kx*Dset;
   
   temp1 =  polysum([temp1.A temp1.b],[temp.A temp.b]);
   [tA,tb] = aug2std(temp1);
   temp1 = Polyhedron('A',tA,'b',tb);
   temp1.b
end
          
% Y_N=(Acl^(N-1))*F*A*Dset_prev + temp;
Y_N=temp1;
Xorig=LiftStateSet;
Zn=Xorig-Y_N;


XX=std2aug(Zn.A,Zn.b);

UU = std2aug(A_input,b_input);

WW = std2aug(A_dist,b_dist);

[k,~,st]=kinfset(A_lift,B_lift,Ln*F,XX,UU,WW,XX,100,1,[]);

[CC.A CC.b]=aug2std(k);

Cdelta=Polyhedron('A',CC.A,'B',CC.b);
