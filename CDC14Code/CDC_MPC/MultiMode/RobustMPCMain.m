function [x_trajectory,x_trajectory_actual,u_applied] = RobustMPCMain(Tsim,Horizon)

%% get plant model(s)

h=0.02; %sampling time
Tc=0.0001; % control computation time
deltas=[.01 0.0025 0.0025/4];
epsilons=[.125 0.5 2 ];
% deltas=[0.0025];epsilons=[0.5];
% new test
Tc=0;
% deltas=10^(-3)*[1 2 4]*2.5;
%epsilons=[0.4 0.2 0.1];%/2.66;

%final versions
deltas=[0.01 .005 .0025];
epsilons=[0.1 0.2 0.4]*2.5;

deltas=0.0025;epsilons=1;

%   deltas=[0.01 0.0025]; %.01 and .0025 switch
%   epsilons=[0.0625 0.25]; %.0625 and .25 switch
 %epsilons=[.2 .4]; % inf norm bounds
% epsilons=[0.2 2];
%  deltas=[0.0025];epsilons=[.32]; %0.01 and eps=0.1; 0.005 and eps=.25 atleast work
Res=[96 64 32];%pic is of Res*Res


% deltas=[0.05];
% epsilons=[1];
No_of_modes=length(deltas);
%sys matrices
A=cell(length(deltas),1);
B1=cell(length(deltas),1);
B2=cell(length(deltas),1);
A_lift=cell(length(deltas),1);
B_lift=cell(length(deltas),1);
K=cell(length(deltas),1);
Kx=cell(length(deltas),1);
Acl=cell(length(deltas),1);

for i=1:No_of_modes%over all modes
    [A{i} B1{i} B2{i}] = plant_model(deltas(i),Tc,h);
    A_lift{i}=[A{i} B1{i};zeros(size(B1{i},2),size(B1{i},2)+size(A{i},2))];
    B_lift{i}=[B2{i};eye(size(B2{i},2))];

    %lqr
    K{i}=-1*dlqr(A_lift{i},B_lift{i},1*eye(size(A_lift{i},1)),1*eye(size(B_lift{i},2)),zeros(size(A_lift{i},1),size(B_lift{i},2))); %A+BK is stable in DT sense
    
    %place
%     K{i}=-.1*place(A_lift{i},B_lift{i},[10^-5;10^-3;10^-4;0;10^-2;eps]);
    Acl{i}=A_lift{i}+B_lift{i}*K{i}; %closed loop,phi
    temp=K{i};
    Kx{i}=temp(:,1:size(A{i},1));
end

F=[eye(size(A{1},2));zeros(size(B1{1},2),size(A{1},2))]; %dist input matrix, constt. throughtout

%% Sets

%init variables
%Tsim=400;
%Horizon=50;

%variables for state/input
x_trajectory=zeros(size(A{1},1),Tsim); %trajectory of center of estimates
u_applied=zeros(size(B1{1},2),Tsim);
x_trajectory_actual=zeros(size(A{1},1),Tsim);

%disturbance set (inf norm bound)
E_set=cell(No_of_modes,1);
for i=1:No_of_modes
   norm_e_inf=epsilons(i); 
   disturbance.A=[eye(size(A{1},1));-eye(size(A{1},1))];
   disturbance.b=norm_e_inf*[ones(size(A{1},1),1);ones(size(A{1},1),1)];
   E_set{i} = Polyhedron('A',disturbance.A,'B',disturbance.b);
end


Dset=E_set{1}; %used for current error set
Dset_prev=E_set{1}; %used for previous error set

%Feasible set (initial) of states and inputs
% x_max=100*ones(size(A{1},1),1);
% x_min=-100*ones(size(A{1},1),1);
% 
% feasible.A=[eye(size(A{1},1));-eye(size(A{1},1))];
% feasible.b=[x_max;-x_min];
% 
% Xset=Polyhedron('A',feasible.A,'B',feasible.b); 

%alt rep (interesting set)
Pos_set=Polyhedron([40 70;100 50;10 -10;-20 -10;-20 20]);



%alt rep (Truong's set)
%  S=Polyhedron([-10 0;0 10;50 10;60 0;50 -10;0 -10]);
 
%  S=Polyhedron([-20 0;-10 10;60 10;70 0;60 -10;0 -20]); %works
   S=Polyhedron([-20 0;0 15;60 15;70 0;60 -15;0 -15]); %used in paper
theta = pi/180*45;
R=[cos(theta) -sin(theta);sin(theta) cos(theta)]; %rotate by 45 deg ccw
Pos_set=R*S;

vel_set=Polyhedron([100 100;100 -100;-100 -100;-100 100]);
Xset=Pos_set*vel_set;

u_max=[10]*ones(size(B2{1},2),1);
u_min=[-10]*ones(size(B2{1},2),1);
feasible.Ainput=[eye(size(B1{1},2));-eye(size(B1{1},2))];
feasible.Binput=[u_max;-u_min];

Uset=Polyhedron('A',feasible.Ainput,'B',feasible.Binput);

Xorig=Xset*Uset; %the big Z set at the start
Xorig.minHRep;

InputSet=Uset; % variables for the terminal set constraints
LiftStateSet=Xorig;

%Get Cdelta sets (terminal)

Cdelta=cell(No_of_modes,1);
for i=1:No_of_modes
    Cdelta{i}=getTermSetCdelta_compute(A{i},Acl{i},F,A_lift{i},B_lift{i},K{i},Kx{i},E_set{i},InputSet,LiftStateSet,epsilons(i),Horizon);
end


%% MPC begins

%initial states
x0=[50]*ones(size(A{1},1),1);
x0=[30;30;0;0];
u0=0*ones(size(B2{1},2),1);
uminus1=zeros(size(B2{1},2),1);
xLo=[x0;u0];
c0=zeros(size(B2{1},2),1);
L=eye(size(A{1},2)+size(B2{1},2));
L0=L;
xtrue=xLo; %init true state

costs=zeros(No_of_modes,1);
cost_history=zeros(Tsim,No_of_modes);
controls=zeros(size(B2{1},2),No_of_modes);
control_applied=zeros(size(B2{1},2));
Mode_picked=zeros(Tsim,1);
ZZtop=cell(No_of_modes,1);
% clear Xset;
%  costs=zeros(No_of_modes,Tsim); %cost for every mode
alpha=0.0;

%begin MPC
for t=1:Tsim %all time
    t
     costs=zeros(No_of_modes,1); %cost for every mode
   
    for mode=1:No_of_modes %for all modes
        Dset = E_set{mode};
        eps = epsilons(mode);
        if(t==1) %at first time set Dset_prev=Dset, only at the first
            Dset_prev=Dset;
            A_lift_prev=A_lift{mode};
            B_lift_prev=B_lift{mode};
            eps_prev=epsilons(mode);
        end
        
        [controls(:,mode) costs(mode) ZZtop{mode}] = RMPC_compute(A{mode},A_lift{mode},B_lift{mode},A_lift_prev,B_lift_prev,B1{mode},B2{mode},K{mode},Kx{mode},Acl{mode},F,xLo,u0,Dset,Dset_prev,Xorig,Cdelta{mode},eps,eps_prev,Horizon);
        costs(mode)=costs(mode)+alpha*Res(mode);

    end
    cost_history(t,:)=costs';
    %pick best mode (check toget rid of infeasible error somehow)
    [c ix]=min(costs);
    Mode_picked(t)=ix;
    control_applied=controls(:,ix);
    Dset_prev=E_set{ix}; %update Dset_prev to that of best mode
%     A_lift_prev=A_lift{ix};
%     B_lift_prev=B_lift{ix};
%     eps_prev=epsilons(ix);
    
    %update system
    xtrue=(A_lift_prev)*xtrue + B_lift_prev*u0;
    xLo=xtrue + ([1-2*rand(size(A{1},1),1);zeros(size(B1{1},2),1)])*eps_prev; %corrupt estimate (only original states)
    u0=control_applied;
    
     A_lift_prev=A_lift{ix};
    B_lift_prev=B_lift{ix};
    eps_prev=epsilons(ix);
    
    
   %store
   x_trajectory(:,t)=xLo(1:size(A{1},1)); %estimates used
   x_trajectory_actual(:,t)=xtrue(1:size(A{1},1),1); %actual pos/vel
   u_applied(:,t)=control_applied; %applied input

end

