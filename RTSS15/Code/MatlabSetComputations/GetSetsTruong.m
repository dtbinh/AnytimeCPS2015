InitPlandAndSets;

set_comps = 0;
Ns = H; %horizon
wmax = 0;
tmax = 1;

Zj = cell(numel(deltas),1);
Z_N = cell(numel(deltas),1);
Cdeltas = cell(numel(deltas),1);
statuses = cell(numel(deltas),1);

for i = 1:numel(deltas)

epsilon = epsilons(i);
sys.B1 = B1_modes(:,:,i);
sys.B2 = B2_modes(:,:,i);
sys.A = A_modes(:,:,i);
SS.H = StateSet.A;
SS.K = StateSet.b;
UU.H = InputSet.A;
UU.K = InputSet.b;
Ln=(A_lift(:,:,i)+B_lift(:,:,i)*K(:,:,i))^(Ns);
Ks = K(:,:,i);
pw=inf;
pe=inf;
Zs = calcSetsFixed(sys,SS,UU,Ns,Ks,pw,pe);
ZN = Zs(end);
ZN.K = ZN.K*[1; wmax; epsilon; epsilon];

[Cd,st] = calcInvSet( sys, ZN, Ln*Fhat, wmax, epsilon, pw, pe, tmax);

Zj{i} = Zs;
Z_N{i} = ZN;
Cdeltas{i} = Cd;
statuses{i} = st;
end