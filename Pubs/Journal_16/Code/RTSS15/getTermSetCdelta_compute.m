function [Cdelta]=getTermSetCdelta_compute(A,Acl,F,A_lift,B_lift,K,Kx,Dset,InputSet,LiftStateSet,eps,Horizon)


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
% 
% for i=2:N
%    
%    Y_N =  plus(-(Acl)^(N-i)*B_lift*Kx*Dset,Y_N);
% end
%           
% % Y_N=(Acl^(N-1))*F*A*Dset_prev + temp;
Xorig=LiftStateSet;

[Za Zb]=getZj(A,Acl,B_lift,Kx,F,Xorig,N,N,eps,eps); %get Z_N(eps,eps)


Zn.A=Za;
Zn.b=Zb;
ZNset=Polyhedron('A',Za,'b',Zb);
if(ZNset.isEmptySet==1)
     exception = MException('Zn:empty', ...
       'Cannot compute Cdelta as Zn is empty for this mode and its settings');
    throw(exception);
end


XX=std2aug(Zn.A,Zn.b);

UU = std2aug(A_input,b_input);

WW = std2aug(A_dist,b_dist);
iters=2;lam=1; %lam=0.1 gets switching but a terrible trajectory
[k,~,st]=kinfset(A_lift,B_lift,Ln*F,XX,UU,WW,XX,iters,lam,[]);

[CC.A CC.b]=aug2std(k);

Cdelta=Polyhedron('A',CC.A,'B',CC.b);
