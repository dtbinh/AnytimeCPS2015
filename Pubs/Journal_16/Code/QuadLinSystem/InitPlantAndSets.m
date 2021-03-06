QuadLinearModel; %get quad dynamics for high level control

%modes of estimation
deltas = [24 30 34 39]*(10^-3);%[0.0125;0.0129;0.0139];%(h/2)*rand(3,1);
epsilons = 1*[0.028;0.0237;0.0231;0.0113;0.01]; %old
epsilons = [0.039 0.035 0.034 0.032];
numModes = numel(deltas);
setComps = 0;
% MPC Horizon
N = 10;

%get plant models for 0these modesls

A_modes = zeros(size(sys_c.a,1),size(sys_c.a,2),numModes);
B1_modes = zeros(size(sys_c.b,1),size(sys_c.b,2),numModes);
B2_modes = zeros(size(B1_modes,1),size(B1_modes,2),numModes);

A_lift = zeros(size(A_modes,1)+size(B1_modes,2),size(A_modes,1)+size(B1_modes,2),numModes);
B_lift = zeros(size(A_lift,1),size(B1_modes,2),numModes);

K = zeros(size(B_lift,2),size(A_lift,1),numModes);
Kx = zeros(size(B1_modes,2),size(A_modes,1),numModes);
Acl = zeros(size(A_lift,1),size(A_lift,2),numModes);

for i = 1:numModes
    [A_modes(:,:,i), B1_modes(:,:,i), B2_modes(:,:,i)]= plant_model(sys_c.a,sys_c.b,deltas(i),0,h);
    A_lift(:,:,i)=[A_modes(:,:,i) B1_modes(:,:,i);zeros(size(B1_modes,2),size(B1_modes,2)+size(A_modes,2))];
    B_lift(:,:,i)=[B2_modes(:,:,i);eye(size(B2_modes,2))];
    %lqr
    K(:,:,i)=-1*dlqr(A_lift(:,:,i),B_lift(:,:,i),1*eye(size(A_lift,1)),1*eye(size(B_lift,2)),zeros(size(A_lift,1),size(B_lift,2))); %A+BK is stable in DT sense
    Acl(:,:,i)=A_lift(:,:,i)+B_lift(:,:,i)*K(:,:,i); %closed loop,phi
    temp=K(:,:,i);
    Kx(:,:,i)=temp(:,1:size(A,1));
    
end

Fhat=[eye(size(A,2));zeros(size(B,2),size(A,2))]; %dist input matrix, constt. throughtout

%% set for states
% safety sets for states and inputs
emptyPoly = Polyhedron();


stateset.A=[eye(size(A,1));-eye(size(A,1))];
stateset.b=repmat(2*[5;5;5;5;5;5],2,1);

StateSet = Polyhedron('A',stateset.A,'B',stateset.b);
clear stateset disturbance

inpLim = [deg2rad(30);deg2rad(30);10]; %P,R,T
inpset.A=[eye(size(B,2));-eye(size(B,2))];
inpset.b=repmat(inpLim,2,1);

InputSet = Polyhedron('A',inpset.A,'B',inpset.b);
clear inptset inpLim

S = StateSet*InputSet;  %Safe set of states and inputs
S.minHRep;

%% Rec feas probability computation
% disturbance means and covs (made up right now):

% make some closed loop L

if(1) %load data or test
    clear dist_params;
    load('../../../MATLAB/SVO_Profiling/Data_2017/SVO_profiling_0.mat')
    %load('../../MATLAB/SVO_Profiling/Data_2017/Perch_SVO.mat')
    for i = 1:numModes
        dist_params(i).cov_e = zeros(6,6);
        c = 1;%2*10^-1;
        dist_params(i).cov_e(1,1) = c*var(Datas(i).err_x);
        dist_params(i).cov_e(4,4) = c*var(Datas(i).err_x);
        dist_params(i).cov_e(2,2) = c*var(Datas(i).err_y);
        dist_params(i).cov_e(5,5) = c*var(Datas(i).err_y);
        dist_params(i).cov_e(3,3) = c*var(Datas(i).err_z);
        dist_params(i).cov_e(6,6) = c*var(Datas(i).err_z);
        dist_params(i).cov_w = 0.00001*eye(6);
        % 95th confidence error rectangle
        MM = dist_params(i).cov_e(1:3,1:3);
        M = minv(MM);
        [lb,ub] = getOuterRect(M);
        dist_params(i).E_95 = Polyhedron('lb',[lb;lb],'ub',[ub;ub]);
    end
else
    %e
    dist_params.u_e = zeros(6,1);
    dist_params.cov_e = 0.03*eye(6);
    dist_params.cov_e =  5.7309e-4*eye(6);
    
    %w
    dist_params.u_w = zeros(6,1);
    dist_params.cov_w = 0.0001*eye(6);
end
%alpha and alpha_is, from (Pr(x\inX)>=1-alpha)
alpha = 0.18;
alpha_is = repmat(alpha/size(S.b,1),size(S.b,1),1);

%% get problem parameters
ProblemParams = RecFeasProb(S,Acl,A_lift,Fhat,N,alpha_is,dist_params);
ProblemParams.n_x = size(sys_c.a,1);
ProblemParams.n_u = size(sys_c.b,2);
% Robust control inv set
Cdelta = repmat(emptyPoly,numModes,1);
%% %% for deterministic RAMPC
if(1)
    epsilons = zeros(numModes,1);
    H = N+1;
    for i = 1:numModes
        i
        epsilons(i) = max(dist_params(i).E_95.b);
        E_set(i) = dist_params(i).E_95;
        Cdelta(i)=getTermSetCdelta_compute(A_modes(:,:,i),Acl(:,:,i), ...
            Fhat,A_lift(:,:,i),B_lift(:,:,i),K(:,:,i),...
            Kx(:,:,i),E_set(i),InputSet,S,epsilons(i),H);
        Cdelta(i) = Cdelta(i).minHRep;
        for k = 0:H %get deterministic Zjs for all modes
            [ZA, Zb] = getZj(A_modes(:,:,i),Acl(:,:,i),B_lift(:,:,i),Kx(:,:,i),Fhat,S,H,k,epsilons(i),epsilons(i));
            Zj_det(i,k+1) = Polyhedron('A',ZA,'B',Zb);
            Zj_det(i,k+1).minHRep;
            if(Zj_det(i,k+1).isEmptySet)
                exception = MException('Zj:empty', ...
                    'Zj empty at i j k= %d %d %d',i,j,k);
                throw(exception)
            end
            
        end
        Zj_det = Zj_det';
    end
else
    
end

%% get Zjs
Zjs = getZjs_smpc(S,ProblemParams,N);

%% save
save('Data/Sets_2017.mat','epsilons','deltas','A_lift','B_lift','Cdelta','Zjs', ...
    'Kx','E_set','K','A_modes','B1_modes','B2_modes','Acl','h','H','S','InputSet', ...
    'dist_params','ProblemParams','Zj_det')
%%

for i = 1:H
    plot(Zj_det(i,1).projection(1:3)-Zjs{i,1}.projection(1:3),'color','red');pause
end


