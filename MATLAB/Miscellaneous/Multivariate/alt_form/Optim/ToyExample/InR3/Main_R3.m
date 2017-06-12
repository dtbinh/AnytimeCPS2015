% 2d example
% (always not Unsfafe) and (eventually Terminal)
%% get params

%clc;close all;
close all;
baron_use = 0;
%clear all;close all;

disp('Initializing problem...');
disp('Loading Map...');
map_name = 'maps/map1.txt';
obs = getObstacles(map_name);
map = load_map(map_name, .5, .5, 0);
plot_path(map, []);
%goal.stop = [9;9;9]; %map2
%goal.stop = [7.5;3;3]; %map1
goal.stop = [5;1;5.5]; %map1
goal.ds = .5;


%% optimization data
disp('Control problem data');
dim = 3;
dim_u = 3;
len = 50;

optParams.dim = dim;
optParams.len = len;
optParams.dim_u = dim_u;

u_lim = 0.5;
% %sample map2
% x_lb = [-0 0 0]';
% x_ub = [10 10 10]';

 %sample map1
 x_lb = [0.5 0 .2]';
 x_ub = [9.5 20 5.95]';

P_feas = Polyhedron('lb',x_lb,'ub',x_ub);
U_feas = Polyhedron('lb',-u_lim*ones(1,dim_u),'ub',u_lim*ones(1,dim_u));

P_term = Polyhedron('lb',goal.stop-goal.ds,'ub',goal.stop+goal.ds);
AuxParams.P_final = P_term;
optParams.P_final.A = P_term.A;
optParams.P_final.b = P_term.b;

AuxParams.U_feas = U_feas;
optParams.U_feas.A = U_feas.A;
optParams.U_feas.b = U_feas.b;
% system dynamics
optParams.A = eye(dim);
optParams.B = eye(dim_u); %dim_u = dim here son
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
%x0 = [1;1;1]; %sample map2
%x0 = [1; 2; 5]; %sample map1
x0 = [5;18;2];
else %in [-2 -1.1]^2
x0 = -2 + (-1.1+2)*rand(3,1);    
end

optParams.gamma = 0;%10^(-2);
optParams.x0 = x0;

optParams.P_feas.A = P_feas.A;
optParams.P_feas.b = P_feas.b;
AuxParams.P_feas = P_feas;

%% redo constraints for control input
% H_U = kron(eye(optParams.len-1),optParams.U_feas.A);
% g_U = repmat(optParams.U_feas.b,optParams.len-1,1);
%sanity check
% stairs(H_U*u_0<=g_U);
%or
LB_U = repmat(-u_lim*ones(size(optParams.B,2),1),optParams.len-1,1);
UB_U = repmat(u_lim*ones(size(optParams.B,2),1),optParams.len-1,1);
dim_u = size(optParams.B,2);
% translate state constraints if needed
A_x0 = [];
for i = 1:optParams.len-1
    A_x0 = [A_x0;optParams.A^i];    
end
%
clear B_U
for i = 1:optParams.len-1
    for j = 1:optParams.len-1
       B_U((i-1)*dim+1:i*dim,(j-1)*dim_u+1:j*dim_u) = (i-j>=0)*optParams.A^(i-j)*optParams.B + (i-j<0)*zeros(size(optParams.A*optParams.B));     
    end
end

optParams.A_x0 = [eye(dim);A_x0];
optParams.B_U = [zeros(optParams.dim,(optParams.len-1)*optParams.dim_u);B_U];
    
X_lims = Polyhedron('lb',repmat(x_lb,optParams.len,1),'ub',repmat(x_ub,optParams.len,1));

H1 = X_lims.A*optParams.B_U;
g1 = X_lims.b-X_lims.A*optParams.A_x0*optParams.x0;
U_new = Polyhedron('A',H1,'b',g1);
U_lims = Polyhedron('lb',LB_U,'ub',UB_U);
U_intersect = intersect(U_new,U_lims);
U_intersect.minHRep;
%% start opt
disp('Getting init trajectory');
% init traj gen
if(1) %via reg MPC
    x_0 = [x0;rand((len-1)*dim,1);rand((len-1)*size(optParams.B,2),1)];
    x_feas = getFeasTraj(x_0,optParams);
    x_0 = x_feas.x0;
    u_0 = x_feas.u(:);
    if(sum(isnan(x_0))>0)
        'x_0 infeasible'
        keyboard;
    end
else
    load('TestData_opt4','x') %from somewhere else
    x_0 = x;
end

%% random initialization
rd_u0 = 0;
if(rd_u0)
   u_0 = -0.25+(.5)*rand(optParams.dim_u*(optParams.len-1),1); %random u_0; 
   rd_u0 = 1;
   x_0 = [optParams.A_x0*optParams.x0 + optParams.B_U*u_0;u_0];
end

%% gen code for objfun and confun

if(0)
    disp('Code gen');
    CodeGeneratorForOptim;
end
%% sanity cheque
if(0)
    path = reshape(optParams.A_x0*optParams.x0 + optParams.B_U*u_0,3,20)';
    getRobustness(path,obs,goal)
    plot_path(map,path)
end
%keyboard
%%  optim
if(exist('robustness_max','var'))
    if(~isempty(robustness_max))
        objLim = -10*robustness_max - eps*(1-robustness_max);
    else
        objLim = -eps;
    end
    
    else
    objLim = -10;
end

%%
clear options;
disp('Robustness maximization')
tic;
options = optimset('Algorithm','sqp','Display','off','MaxIter',1000,'TolConSQP',1e-2,...
    'ObjectiveLimit',objLim,'UseParallel','always','MaxFunEval',1000000,'GradObj','off'); %rep 'always' by true
%options.TolFun = 10^(-10);
%options.TolCon = 10;
%[x,fval,flag] = ...

%[u_opt,fval,exitflag,output] = fmincon(@(u)main_objfun2_u_toy_using_mex(u,optParams),u_0,U_intersect.A,U_intersect.b,[],[],[],[],[],options);
if(~baron_use)
[u_opt,fval,exitflag,output] = fmincon(@(u)getRobustness_u(u,obs,goal,optParams),u_0,U_intersect.A,U_intersect.b,[],[],[],[],[],options);

else
not_so_fun = @(u) getRobustness_u_Baron(u,obs,goal,optParams);
[u_opt,fval,ef,info] = baron(not_so_fun,U_intersect.A,-inf(numel(U_intersect.b),1), ...
    U_intersect.b,...
    [],[],[],[],[],[],[],baronset('threads',3,'sense','min','tracefile',...
    'barouttrac.out','filekp',1,'barscratch','shizzle.out','dolocal',0)) 
end


time_taken = toc

%% plot
if(exist('display_on','var'))
    if(display_on)
        disp_plot=1;
    else
        disp_plot=0;
    end
else
    disp_plot = 1;close all;
end

if(disp_plot)
    
path_opt = reshape(optParams.A_x0*optParams.x0 + optParams.B_U*u_opt,optParams.dim,optParams.len)';
plot(P_term,'alpha',0.2,'color','green');
axis([0 10 0 10 0 10]);
hold on;
plot_path(map,path_opt);
hold on;

end