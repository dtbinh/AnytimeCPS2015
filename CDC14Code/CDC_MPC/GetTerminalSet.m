% compute terminal set

Ln=(A_lift+B_lift*K)^(Horizon);

A_state = LiftStateSet.A;
b_state = LiftStateSet.b;
A_input = InputSet.A;
b_input = InputSet.b;


Wset=-Dset+A*Dset;

A_dist = Wset.A;
b_dist = Wset.b;

% XX = std2aug(A_state,b_state);
%Calculate Zn for state constraints
temp=zeros(size(xLo,1),1); %to initialize temp, how do I get empty set here instead of zeros?

N=Horizon;
for ii=2:N-1
   temp =  plus(-(Acl)^(N-1-ii)*B_lift*Kx*Dset,temp);
end
          
Y_N=(Acl^(N-1-1))*F*A*Dset_prev + temp;

Zn=Xorig-Y_N;


XX=std2aug(Zn.A,Zn.b);

%
UU = std2aug(A_input,b_input);

WW = std2aug(A_dist,b_dist);

%[k,~,st]=kinfset(A_lift,B_lift,F,XX,UU,WW,XX,1,0.9); % this is ok if WW is
%a the dist set, for now, set W is empty (no w disturbance)

%[k,~,st]=kinfset(A_lift,B_lift,F,XX,UU,[],XX,1,0.9); % this works

% [k,~,st]=kinfset(A_lift,B_lift,Ln*F,XX,UU,WW,XX,10,1,[]);
[k,~,st]=kinfset(A_lift,B_lift,Ln*F,XX,UU,WW,XX,100,1,[]);

[CC.A CC.b]=aug2std(k);

Cdelta=Polyhedron('A',CC.A,'B',CC.b);

What = (-Dset)+A*Dset_prev;
Zf = Cdelta - Ln*F*What;