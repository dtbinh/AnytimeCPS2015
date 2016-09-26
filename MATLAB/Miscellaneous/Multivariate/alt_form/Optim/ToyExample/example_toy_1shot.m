% example 4, optimization
% (always not P1)

%% get params
P1 = Polyhedron('lb',[-1 -1],'ub',[1 1]);
xmin = -5;
xmax = 5;
dx = 0.1;

optional_P1.filename = 'P1_j0_P.mat';
optional_P1.savefile = 'P1_j0_P.mat';

[Params_P1] = WavSignedDistVector(P1,xmin,xmax,dx,0,optional_P1);

%pause;
close all;clc;
%plot(P1);hold all;plot(P2);



%% optimization data
dim = 2;
len = 5;

P_feas = Polyhedron('lb',[-2.5 -2.5],'ub',[2.5 2.5]);
P_final = Polyhedron('lb',[2 2],'ub',[2.5 2.5]);
U_feas = Polyhedron('lb',[-1 -1],'ub',[1 1]); % input set

optParams.P_final = P_final;
optParams.U_feas = U_feas;
%system dynamics
optParams.A = eye(2);
optParams.B = eye(2);


%save('OptParams.mat','x0','P1','Params_P1','P2','Params_P2','dim','len');
x0 = [-2;-2];
x0 = [-1.5;0];

optParams.x0 = x0;
optParams.dim = dim;
optParams.len = len;
optParams.Params_P1 = Params_P1;
%optParams.Params_P2 = Params_P2;
optParams.P1 = P1;
%optParams.P2 = P2;
optParams.P_feas = P_feas;
%% start opt
clc;
%x_0 = [x0;-1.2;-1.0];%make an initial trajectory that is feas (can be infeas)
%x_0 = x0;
% search variable is states first, then inputs. Within the states, all
% states at time 1, then all states at time 2, etc.
% [x1(0),x2(0),...,xn(0), x1(1), x2(2), etc, u(0),...]
x_0 = [x0;rand((len-1)*dim,1);rand((len-1)*size(optParams.B,2),1)];
x_feas = getFeasTraj(x_0,optParams);
x_0 = x_feas.x0;
%x_0 = [x0;[-1.5;1];[-0.5
%%  optim

options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000);
%options.TolFun = 10^(-10);
%options.TolCon = 10;
%[x,fval,flag] = ... 
[x,fval,exitflag,output] = fmincon(@(x)objfun_toy(x,optParams),x_0,[],[],[],[],[],[], ...
@(x)confun_toy(x,optParams),options)

