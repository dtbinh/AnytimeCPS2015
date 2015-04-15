PlantModelQuadSimpleLinear; %get quad dynamics for high level control

%modes of estimation
deltas = (h/2)*rand(3,1);
epsilons = rand(3,1);
numModes = numel(deltas);

%get plant models for these modes
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

F=[eye(size(A,2));zeros(size(B,2),size(A,2))]; %dist input matrix, constt. throughtout

%% set for states

% est error sets
disturbance.A=[eye(size(A,1));-eye(size(A,1))];
emptyPoly = Polyhedron();
E_set = repmat(emptyPoly,numModes,1);

% get inf norm reps

for i=1:numModes
    disturbance.b=epsilons(i)*[ones(size(A,1),1);ones(size(A,1),1)];
    E_set(i) = Polyhedron('A',disturbance.A,'B',disturbance.b);
    E_set(i).minHRep;
end

% safety sets for states and inputs

stateset.A=[eye(size(A,1));-eye(size(A,1))];
stateset.b=repmat([100;100;100;10;10;10],2,1);

StateSet = Polyhedron('A',stateset.A,'B',stateset.b);
clear stateset emptyPoly disturbance 

inpLim = [deg2rad(30);deg2rad(30);10]; %P,R,T
inpset.A=[eye(size(B,2));-eye(size(B,2))];
inpset.b=repmat(inpLim,2,1);

InputSet = Polyhedron('A',inpset.A,'B',inpset.b);
clear inptset inpLim

S = StateSet*InputSet;  
