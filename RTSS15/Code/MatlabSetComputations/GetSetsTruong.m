sys.B1 = B1_modes(:,:,1);
sys.B2 = B2_modes(:,:,1);
sys.A = A_modes(:,:,1);
SS.H = StateSet.A;
SS.K = StateSet.b;
UU.H = InputSet.A;
UU.K = InputSet.b;
Ns = 10;
Ks = K(:,:,1);
pw=inf;
pe=inf;

Zs = calcSetsFixed(sys,SS,UU,Ns,Ks,pw,pe);