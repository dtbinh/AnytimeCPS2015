%% case study main
clc;clear all;close all;
%general options
genCode =0;
genCodeCostFn = 0;
getCoeffs = 0;
getRuleCoeffs = 0;
baron_use = 0;

% load maps
disp('Initializing problem...');
disp('Loading Map...');
map_name = 'maps/map1.txt';
obs = getObstacles(map_name);
map = load_map(map_name, .5, .5, 0);
plot_path(map, []);
goal.stop = [5;1;5.5]; %map1
goal.ds = .5;


%% sys dynamics
g = 9.8;
m = 0.5;
h = 1/20; %5Hz

tempA = sparse(6,6);
%tempA(1:3,4:6) = eye(3);
tempA(4:6,1:3) = eye(3);
tempB = sparse(6,3);
%tempB(4,1) = g;
%tempB(5,2) = -g;
%tempB(6,3) = 1/m;
tempB(1,1) = g;
tempB(2,2) = -g;
tempB(3,3) = 1/m;

sys_c = ss(tempA,tempB,eye(6),zeros(6,3));
sys_d = c2d(sys_c,h);


%% optim para

optParams.dim_x = 6;
optParams.dim_u = 3;
optParams.len = 125; % 50 works well for 5;5;4.5; 75 for 5;10;4.5
optParams.A = sys_d.A;
optParams.B = sys_d.B;

%input bounds
max_ang = deg2rad(30);
max_thr = 2.5; % 2.5 works well for 2 cases

%state bounds
temp = Polyhedron('lb',[-max_ang -max_ang -max_thr],'ub',[max_ang max_ang max_thr]);
optParams.U_feas.A = temp.A;
optParams.U_feas.b = temp.b;

temp = Polyhedron('lb',[-5*ones(3,1);0.5; 0; 0.2],'ub',[5*ones(3,1);9.5; 20; 5.95]); %feas set
optParams.P_feas.A = temp.A;
optParams.P_feas.b = temp.b;

optParams.robCost = 1;
optParams.robConstr = 0;
optParams.gamma = 0;



%% initialize optimization
disp('Initial trajectory...');

Terminal = Polyhedron('lb',goal.stop-goal.ds,'ub',goal.stop+goal.ds);
Terminal_velocities = Polyhedron('lb',-1*ones(3,1),'ub',1*ones(3,1));
temp = Terminal_velocities*Terminal;
optParams.P_final.A = temp.A;
optParams.P_final.b = temp.b;
P_term = Terminal;


x1 = zeros(optParams.len*optParams.dim_x+ (optParams.len-1)*optParams.dim_u,1); %for one quad
% x1(4:6) = [5;18;2]; %init positions

% x1(4:6) = [5;5;3]; %init positions, works len 50, c = 30
% x1(4:6) = [5;5;4]; %init positions, works ditto
% x1(4:6) = [5;10;4.5];
x1(4:6) = [3;17;2.5];
optParams.x0 = x1(1:6);
x1_feas = getFeasTraj_case(x1,optParams);
% x2 = zeros(optParams.len*optParams.dim_x+ (optParams.len-1)*optParams.dim_u,1); %for one quad
% x2(4:6) = [-2 -2 2];
% x2_feas = getFeasTraj_case(x2,optParams);

% init states for the optimization
optParams.x0_1 = x1(1:6);
% optParams.x0_2 = x2(1:6);

%x_0 =[x1_feas.x0;x2_feas.x0]; %starting point of opt (a trajectory)
u1_0 = x1_feas.u(:);
u_0 = u1_0;
%u2_0 = x2_feas.u(:);
if(sum(isnan(x1_feas.z(:)))>10)
    disp('Infeasible goal');
    keyboard;
end
%plot init trajs
figure(1);
for i = 1:optParams.len
    hold on;
    plot3(x1_feas.z(4,i),x1_feas.z(5,i),x1_feas.z(6,i),'b*')
    %    hold on
    %    plot3(x2_feas.z(4,i),x2_feas.z(5,i),x2_feas.z(6,i),'ro');
end
grid on;
zlabel('z');
pause(.25);
%% Constraints from the input side
disp('Getting Constraints...');
U_lower = [-max_ang -max_ang -max_thr]';
U_upper = [max_ang max_ang max_thr]';
LB_U = repmat(U_lower,(optParams.len-1),1);
UB_U = repmat(U_upper,(optParams.len-1),1);
X_lower = [-5*ones(3,1);0.5; 0; 0.2];
X_upper  =[5*ones(3,1);9.5; 20; 5.95];
LB_X = repmat(X_lower,optParams.len,1);
UB_X = repmat(X_upper,optParams.len,1);

[~, ceq,~,Aeq] = confun_SingleQuad_case_Baron(x1_feas.x0,optParams); %test to get dims
A_large = eye(size(Aeq))-Aeq;
lbg = [];
ubg = [];
tol_eq = 10^-4;
lbg = [lbg;-tol_eq*ones(size(ceq))];
ubg = [ubg;+tol_eq*ones(size(ceq))];

% add init constraint x0<=x(1:6)-zeros*x(1:6)<=x0
lbg(1:optParams.dim_x) = optParams.x0-tol_eq;
ubg(1:optParams.dim_x) = optParams.x0+tol_eq;
lbx = [LB_X;LB_U];
ubx = [UB_X;UB_U];

% get rid of zero elements
A_large = A_large(1:optParams.dim_x*optParams.len,:);
lbg = lbg(1:optParams.dim_x*optParams.len,:);
ubg = ubg(1:optParams.dim_x*optParams.len,:);
%keyboard;



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
optParams.dim = optParams.dim_x;
clear options;
disp('Robustness maximization...')
tic;
options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000,'TolConSQP',1e-2,...
    'ObjectiveLimit',objLim,'UseParallel','always','MaxFunEval',1000000,'GradObj','off'); %rep 'always' by true
%options.TolFun = 10^(-10);
%options.TolCon = 10;
%[x,fval,flag] = ...

%[u_opt,fval,exitflag,output] = fmincon(@(u)main_objfun2_u_toy_using_mex(u,optParams),u_0,U_intersect.A,U_intersect.b,[],[],[],[],[],options);
if(~baron_use)
    [u_opt,fval,exitflag,output] = fmincon(@(u)getRobustness_u_quad_Baron_full(u,obs,goal,optParams),x1_feas.x0,...
        [],[],A_large,[optParams.x0;zeros(optParams.dim*(optParams.len-1),1)],lbx,ubx,[],options);
    
else
    not_so_fun = @(u) getRobustness_u_quad_Baron_full(u,obs,goal,optParams);
    
    [u_opt,fval,ef,info] = baron(not_so_fun,A_large,lbg, ...
        ubg,...
        lbx,ubx,[],[],[],[],[],baronset('threads',3,'sense','min','dolocal',0,'tracefile','barouttrac.out','filekp',1,'barscratch','shizzle1.out','dolocal',0));
end

% 30 as C in smin/smax works for x0 of 5 5 3
time_taken = toc

%% plot
disp('Plotting...');
disp('Plotting...');
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
    figure(1);
    w_opt = u_opt;
    Nx = optParams.dim_x;
    N = optParams.len;
    x = w_opt(1:optParams.len*optParams.dim_x);
    path_temp = reshape(x(1:Nx*N),Nx,N)';


    path_opt = path_temp(:,4:6); %where quad x y z are
    plot(P_term,'alpha',0.2,'color','green');
    hold on;
    plot_path(map,path_opt);
    hold on;
    figure(2);
    for i = 611:616
        subplot(i);
        plot(path_temp(:,i-610));
        grid on;
    end
end
