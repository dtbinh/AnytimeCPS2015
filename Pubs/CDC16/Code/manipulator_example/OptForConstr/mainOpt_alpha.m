%make a function of this G
%% constraints
load('SetsAndParams.mat');
[~,ubx,lbx] = getRect(Xreach);


%% opts
%max alpha

% start with sim annealing

x0 = zeros(4,1);
[xopt] = simann('objfun_alpha_max',x0,lbx,ubx, ...
    1000,.5,5,20,100);
fopt_simann = feval('objfun_alpha_max',xopt)

% refine with sqp
x0 = xopt;
options = optimset('Algorithm','sqp');
[x,fval] = ... 
fmincon(@objfun_alpha_max,x0,[],[],[],[],[],[],@confun_alpha,options)
max_alpha = -fval;



%min alpha

% start with sim annealing
x0 = zeros(4,1);
[xopt] = simann('objfun_alpha_max',x0,-1*[pi/2;pi/2;pi/4;pi/3],[pi/2;pi/2;pi/4;pi/3], ...
    1000,.5,5,20,100);
fopt_simann = feval('objfun_alpha_max',xopt)

% refine with sqp
x0 = xopt;
options = optimset('Algorithm','sqp');
[x,fval] = ... 
fmincon(@objfun_alpha_max,x0,[],[],[],[],[],[],@confun_alpha,options)
min_alpha = fval;


