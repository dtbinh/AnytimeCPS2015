%% init and get sets
computation = 0;
InitPlandAndSets;

set_comps = 0;
Ns = H; %horizon
wmax = 0;
tmax = 100;
if(computation)
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
    
end
%% get box form for Zf
Z_final= cell(numel(deltas),1);
Zf_box = cell(numel(deltas),1);
CD = cell(numel(deltas),1);
for i = 1:numel(deltas)
    tempW = sys.A*E_set(i) + (-E_set(i));
    CD{i} = Polyhedron('A',Cdeltas{i}.H,'B',Cdeltas{i}.K);
    assert(~CD{i}.isEmptySet);
    Z_final{i} = CD{i} - ((A_lift(:,:,i)+B_lift(:,:,i)*K(:,:,i))^(Ns))*Fhat*tempW;
    Zf_box{i} = FitBoxZf(Z_final{i},S);
end

for i = 1:numel(deltas)
    for k = 1:Ns+1
        Zj{i}(k).A = Zj{i}(k).H;
        Zj{i}(k).b = Zj{i}(k).K*[1;0;epsilons(i);epsilons(i)];
        
        
    end
end
save('~/Documents/AnytimeCPS2015/RTSS15/Code/MatlabSetComputations/Data/SetsT.mat');


