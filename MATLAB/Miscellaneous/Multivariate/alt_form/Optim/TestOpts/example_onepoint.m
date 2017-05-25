% example 4, optimization
% (always not P1) AND/OR (min/max) (always not P2)

%% get params
xmin = -5;
xmax = 5;
dx = 0.25;
P1 = Polyhedron('lb',[-1 -1],'ub',[1 1])
optional_P1.filename = 'P1_j2_P.mat';
optional_P1.savefile = 'P1_j2_P.mat';


[Params_P1] = WavSignedDistVector(P1,xmin,xmax,dx,0,optional_P1);

%plot(P1);hold all;plot(P2);

%% optimization data
x0 = zeros(2,1);%[-2.5;1.5];
dim = 2;
len = 1;
P_feas = Polyhedron('lb',[-2.5 -2.5],'ub',[2.5 2.5]);
%save('OptParams.mat','x0','P1','Params_P1','P2','Params_P2','dim','len');
optParams.x0 = x0;
optParams.dim = dim;
optParams.len = len;
optParams.Params_P1 = Params_P1;
figure;
plot(P_feas);
hold on
plot(P1,'Color','gray');
%% codegen the cost fn
if(1)
    %need gcc 4.8 if parallel stuff is being codegen
cfg=coder.config('mex');
arg_ins = {coder.typeof(x0),coder.typeof(optParams)};
codegen -config cfg objfun_linear -report -args arg_ins
end
%% start opt
clc;
x_0 = x0;
lb = [-2.5;-2.5];
ub = [2.5;2.5];
options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000,'GradObj','on');
%options = optimset('GradObj','on');
%options.TolFun = 10^(-10);
%options.TolCon = 10;
%[x,fval,flag] = ... 
tic;
[x,fval,exitflag,output] = fmincon(@(x)objfun_linear_mex(x,optParams),x_0,[],[],[],[],lb,ub, ...
[],options)
toc
