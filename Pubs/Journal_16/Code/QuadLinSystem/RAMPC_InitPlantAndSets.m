PlantModelQuadSimpleLinear; %get quad dynamics for high level control

%modes of estimation
deltas = [24 30 34 39]*(10^-3);%[0.0125;0.0129;0.0139];%(h/2)*rand(3,1);

%epsilons = 1*[0.028;0.0237;0.0231;0.0113;0.01];%old, for new
load('Data/Sets_2017','E_set');
for i = 1:numel(E_set)
   epsilons(i) =  max(abs(E_set(i).b));
end
%epsilons = [0.0140 0.0130 0.0129 0.0128]; %from set_2017_svo

numModes = numel(deltas);
setComps = 1;
% MPC Horizon
H = 10;

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
% Robustt control inv set
Cdelta = repmat(emptyPoly,numModes,1);
if(setComps)
for i = 1:numModes
    
    Cdelta(i)=getTermSetCdelta_compute(A_modes(:,:,i),Acl(:,:,i), ...
        Fhat,A_lift(:,:,i),B_lift(:,:,i),K(:,:,i),...
        Kx(:,:,i),E_set(i),InputSet,S,epsilons(i),H);
end

% Feas sets for all possible k-1 and (k to k+H) period settings of modes
Zj = repmat(emptyPoly,numModes,numModes,H+1);
%Zf = repmat(emptyPoly,numModes,numModes); %term set

for i = 1:numModes %all modes at k-1
    for j = 1:numModes %all modes from k to k+H
        for k = 0:H %for all in the horizon
            [ZA, Zb] = getZj(A_modes(:,:,j),Acl(:,:,j),B_lift(:,:,j),Kx(:,:,j),Fhat,S,H,k,epsilons(i),epsilons(j));
            Zj(i,j,k+1) = Polyhedron('A',ZA,'B',Zb);
            Zj(i,j,k+1).minHRep;
            if(Zj(i,j,k+1).isEmptySet)
                exception = MException('Zj:empty', ...
                    'Zj empty at i j k= %d %d %d',i,j,k);
                throw(exception)
            end
        end
        %Zfsiz
       
    end
end

%% save stuff
save('Data/Sets.mat','epsilons','deltas','A_lift','B_lift','Cdelta','Zj', ...
    'Kx','E_set','K','A_modes','B1_modes','B2_modes','Acl','h','H','S','InputSet')

end
