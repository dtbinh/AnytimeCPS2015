% example 4, optimization
% (always not P1) AND/OR (min/max) (always not P2)
	tic
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
	%% optimization data
	dim = 2;
	len = 30;

	P_feas = Polyhedron('lb',[-2.5 -2.5],'ub',[2.5 2.5]);
	P_final = Polyhedron('lb',[2.0 2.0],'ub',[2.5 2.5]);
	U_feas = Polyhedron('lb',[-0.32 -0.32],'ub',[0.32 0.32]);
	%U_feas = Polyhedron('lb',[-2.52 -2.52],'ub',[2.52 2.52]);


	optParams.P_final = P_final;
	optParams.U_feas = U_feas;
	%system
	optParams.A = eye(2);
	optParams.B = eye(2);
	% robustness in obj and/or constr
	optParams.robCost = 0;
	optParams.robConstr = 1;

	x0 = [-2;-2];
	%	x0 = [-1.5;0];
	optParams.gamma = 10^(0);
	optParams.x0 = x0;
	optParams.dim = dim;
	optParams.len = len;
	optParams.Params_P1 = Params_P1;
	optParams.P1 = P1;
	optParams.P_feas = P_feas;
	%% start opt
	clc;
	% init traj gen
	if(0) %via reg MPC
	x_0 = [x0;rand((len-1)*dim,1);rand((len-1)*size(optParams.B,2),1)];
	x_feas = getFeasTraj(x_0,optParams);
	x_0 = x_feas.x0;
if(sum(isnan(x_0))>0)
	'x_0 infeasible'
	keyboard;
	end
	else
	load('TestData_opt4','x') %from somewhere else
	x_0 = x;
	end
	%x_0 = [x0;[-1.5;1];[-0.5
	'got init traj'
	%%  optim

	options = optimset('Algorithm','sqp','Display','iter','MaxIter',1000,'TolConSQP',1e-8,...
			'UseParallel',true,'MaxFunEval',1000000);
	%options.TolFun = 10^(-10);
	%options.TolCon = 10;
	%[x,fval,flag] = ... 
	[x,fval,exitflag,output] = fmincon(@(x)objfun_toy(x,optParams),x_0,[],[],[],[],[],[], ...
			@(x)confun_toy(x,optParams),options)

	save('Data/TestData_opt7.mat','x','x_0','optParams');
	time_taken_mins = toc/60;
