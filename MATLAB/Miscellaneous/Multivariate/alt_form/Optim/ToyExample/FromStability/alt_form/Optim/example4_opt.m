% example 4, optimization
% (always not P1) AND/OR (min/max) (always not P2)

%% get params
P1 = Polyhedron('lb',[-1 -1],'ub',[1 1]);
P2 = Polyhedron('lb',[1 1],'ub',[2 2]);
xmin = -5;
xmax = 5;
dx = 0.1;

optional_P1.filename = 'P1_j0_P.mat';
optional_P1.savefile = 'P1_j0_P.mat';
%optional_P2.filename = 'P2_j0_P.mat';
%optional_P2.savefile = 'P2_j0_P.mat';


[Params_P1] = WavSignedDistVector(P1,xmin,xmax,dx,0,optional_P1);
%[Params_P2] = WavSignedDistVector(P2,xmin,xmax,dx,0,optional_P2);
%pause;
close all;clc;
%plot(P1);hold all;plot(P2);

%% optimization data
x0 = [0;0];
dim = 2;
len = 2;
P_feas = Polyhedron('lb',[-2.5 -2.5],'ub',[2.5 2.5]);
P_final = Polyhedron('lb',[2 2],'ub',[2.5 2.5]);
optParams.P_final = P_final;
%save('OptParams.mat','x0','P1','Params_P1','P2','Params_P2','dim','len');
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
x_0 = [x0;-1.2;-1.0];%make an initial trajectory that is feas (can be infeas)
%x_0 = x0;
options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000);
%options.TolFun = 10^(-10);
%options.TolCon = 10;
%[x,fval,flag] = ... 
[x,fval,exitflag,output] = fmincon(@(x)objfun_linear(x,optParams),x_0,[],[],[],[],[],[], ...
@(x)confun_linear(x,optParams),options)

