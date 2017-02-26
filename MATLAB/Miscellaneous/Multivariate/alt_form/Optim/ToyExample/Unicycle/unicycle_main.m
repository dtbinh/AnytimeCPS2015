% 2d example
% (always not Unsfafe) and (eventually Terminal)
%% get params
%unsafe set
%clc;clear all;close all;
close all; unicycle_mode = 1;
%%
disp('Setting up problem...')

%Polyhedrons for the APs
P_unsafe = Polyhedron('lb',[-1 -1],'ub',[1 1]);
P_term = Polyhedron('lb',[2 2],'ub',[2.5 2.5]);

% grid to make up hypercube for wavelet param computations
xmin = -5;
xmax = 5;
dx = 0.25;

% prelim set stuff and 
clear SmoothOpt;
global taliro_SmoothRob; %flag
global SmoothOpt; %params
taliro_SmoothRob = 0;
genCode = 0;
preds(1).A = P_unsafe.A;
preds(1).b = P_unsafe.b;
preds(2).A = P_term.A;
preds(2).b = P_term.b;

% structure with params for wavelets
for i = 1:numel(preds)
    SmoothOpt.preds.Sets(i).A = preds(i).A;
    SmoothOpt.preds.Sets(i).b = preds(i).b;
    SmoothOpt.preds.WavParams(i).k_min = -20;
    SmoothOpt.preds.WavParams(i).k_max = 20;
    SmoothOpt.preds.WavParams(i).j_min = 0;
    SmoothOpt.preds.WavParams(i).j_max = 0;
    SmoothOpt.preds.WavParams(i).x_min = -5;
    SmoothOpt.preds.WavParams(i).x_max = 5;
    SmoothOpt.preds.WavParams(i).dx = 0.25;
    %SmoothOpt.preds.WavParams(i) = wavparams;
end

%% get params wavelet params
disp('Wavelet parameters...')
getParams = 0; %don't set to 1 unless param data is not present
if(getParams) %do this once, disable flag and load params next time
wavparams_all = getWaveletParameters(SmoothOpt,genCode);    
    for i = 1:numel(preds)
        
        SmoothOpt.preds.WavParams(i).E = wavparams_all(i).E;
        SmoothOpt.preds.WavParams(i).E_dash = wavparams_all(i).E_dash;
        SmoothOpt.preds.WavParams(i).D_ejk = wavparams_all(i).D_ejk;
        SmoothOpt.preds.WavParams(i).C_00k = wavparams_all(i).C_00k;
        
    end
    save('Wavparams2_j0_k20_ToyExample.mat','SmoothOpt','wavparams_all');
else
    load('Wavparams2_j0_k5_ToyExample.mat');
end


%pause;
%close all;clc;

%% optimization data
dim = 3; %dimension of state
len = 20; %length of trajectory
optParams.len = len;
optParams.dim = dim;
optParams.dim_u = 2;
optParams.h = 0.1; %discretization period
P_feas = Polyhedron('lb',[-2.5 -2.5 -deg2rad(88)],'ub',[2.5 2.5 deg2rad(88)]); %feasible set of states
U_feas = Polyhedron('lb',[-5 -1],'ub',[5 1]); %input bounds

AuxParams.P_final = P_term;
optParams.P_final.A = P_term.A;
optParams.P_final.b = P_term.b;

AuxParams.U_feas = U_feas;
optParams.U_feas.A = U_feas.A;
optParams.U_feas.b = U_feas.b;

%system dynamics
optParams.A = eye(2);
optParams.B = eye(2);
% robustness in obj and/or constr
optParams.robCost = 1;
optParams.robConstr = 0;




%% init state
if(~exist('rand_x0','var'))
fixed_x0 = 1;
else
   fixed_x0 = ~rand_x0; 
end

if(fixed_x0);
x0 = [-2;-2;0];
else %in [-2 -1.1]^2
x0 = [-2 + (-1.1+2)*rand(2,1);0];    
end
%x0 = [-1.5;0];
optParams.gamma = 0.0;%10^(-2);
optParams.x0 = x0;
optParams.Params_P_unsafe = SmoothOpt.preds.WavParams(1);
optParams.Params_P_term = SmoothOpt.preds.WavParams(2);

optParams.P_feas.A = P_feas.A;
optParams.P_feas.b = P_feas.b;
optParams.P_unsafe.A = P_unsafe.A;
optParams.P_unsafe.b = P_unsafe.b;
AuxParams.P_unsafe = P_unsafe;
AuxParams.P_feas = P_feas;


%% start opt
%clc;
% init traj gen
disp('Getting initial trajectory...');
random_initialization = 1;
rd_u0 = random_initialization;
if(~random_initialization) %via reg MPC
    x_0 = [x0;rand((len-1)*dim,1);rand((len-1)*size(optParams.B,2),1)];
    x_feas = getFeasTraj(x_0,optParams);
    x_0 = x_feas.x0;
    if(sum(isnan(x_0))>0)
        'x_0 infeasible'
        keyboard;
    end

else
   h = optParams.h; 
   rd_u0 = 1;
   u0 = .5*(randn((optParams.len-1)*optParams.dim_u,1));
   uu = reshape(u0,optParams.dim_u,optParams.len-1);
   uu(1,:) = 3.25;
   uu(2,:) = .75;
   xx = zeros(optParams.dim,optParams.len);
   xx(:,1) = x0;
   for t = 2:optParams.len;
    xx(1,t) = (xx(1,t-1) + h*uu(1,t-1)*cos(xx(3,t-1)));
    xx(2,t) = (xx(2,t-1) + h*uu(1,t-1)*sin(xx(3,t-1)));
    xx(3,t) = (xx(3,t-1) + h*uu(2,t-1));
    end
   plot(xx(1,:),xx(2,:))
   x_0 = [xx(:);uu(:)];
  
end

%% gen code for objfun and confun
optParams.dim_x = 2; %dim of formulae
if(0) %make this 1 once, then set to zero 
    disp('Generating code for robustness functions');
CodeGeneratorForOptim;
end


%%  optim
disp('Optimizing...')
global ct;
ct = 0;
tic;
options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000,'TolConSQP',1e-6,'ObjectiveLimit',-0.3,...
    'UseParallel','always','MaxFunEval',1000000,'GradObj','off'); %rep 'always' by true
options.TolFun = 10^(-5);
%options.TolCon = 10;
%[x,fval,flag] = ...
[x,fval,exitflag,output] = fmincon(@(x)objfun2_unicycle(x,optParams),x_0,[],[],[],[],[],[], ...
    @(x)confun2_unicycle(x,optParams),options);


%save('Data/TestData_toyexample2_shite.mat','x','x_0','optParams','AuxParams','SmoothOpt');
time_taken = toc
fval

%% plot
traj_x = reshape(x(1:dim*len),dim,len);
traj_x0 = reshape(x_0(1:dim*len),dim,len);
if(1)
%%
    disp('Plotting...');
dim = optParams.dim;
P_feas = AuxParams.P_feas;
P_final = AuxParams.P_final;
len = optParams.len;
P_unsafe = AuxParams.P_unsafe;
if(dim<=3)
    figure;
    %plot(P_feas,'Color','gray','Alpha',0.7);
    hold on;
    plot(P_unsafe,'Color','red','Alpha',0.7);
    hold on;
    plot(P_final,'Color','green','Alpha',0.7);
    hold on;
    
    hold on;
    
    for i = 1:len
        plot(traj_x0(1,i),traj_x0(2,i),'bo');hold on;
        plot(traj_x(1,i),traj_x(2,i),'k*');hold on;
        pause(.1);
        if(i==2)
            legend('Feasible set','Unsafe set','Terminal Set','Init. Traj.',...
                'Traj. \gamma=0.1');
        end
    end
    grid on;axis([-2.5 2.5 -2.5 2.5]);
end

end
