QuadLinearModel; %get quad dynamics for high level control

%modes of estimation
deltas = [24 30 34 39 45]*(10^-3);%[0.0125;0.0129;0.0139];%(h/2)*rand(3,1);
epsilons = 1*[0.028;0.0237;0.0231;0.0113;0.01];
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

%e
dist_params.u_e = zeros(6,1);
dist_params.cov_e = 0.01*eye(6);

%w
dist_params.u_w = zeros(6,1);
dist_params.cov_w = 0.001*eye(6);

%alpha and alpha_is
alpha = 0.18;
alpha_is = repmat(alpha/size(S.b,1),size(S.b,1),1);

Pr_rec_feas = RecFeasProb(S,Acl,A_lift,Fhat,N,alpha_is,dist_params); %note, cov_What

% Robustt control inv set
Cdelta = repmat(emptyPoly,numModes,1);
