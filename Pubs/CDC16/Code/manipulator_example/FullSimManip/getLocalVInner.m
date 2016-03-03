function [V_inner_local] = getLocalVInner(X_k,U,params)
%function [V_inner_local] = getLocalVInner(X_k,U,params)
%% constraints
Xreach = X_k;
[~,ubx,lbx] = getRect(Xreach);
[~,mxu,mnu] = getRect(U);
save('SetsAndParams.mat','Xreach','-append');

%% opts
%max alpha

% start with sim annealing

x0 = zeros(4,1);
[xopt] = simann('objfun_alpha_max',x0,lbx,ubx, ...
    1000,.5,5,20,100);
fopt_simann = feval('objfun_alpha_max',xopt);

% refine with sqp
x0 = xopt;
options = optimset('Algorithm','sqp','Display','off');
[x,fval] = ... 
fmincon(@objfun_alpha_max,x0,[],[],[],[],[],[],@confun_alpha,options);
max_alpha = -fval;



%min alpha

% start with sim annealing
x0 = zeros(4,1);
[xopt] = simann('objfun_alpha_max',x0,lbx,ubx, ...
    1000,.5,5,20,100);
fopt_simann = feval('objfun_alpha_max',xopt);

% refine with sqp
x0 = xopt;
options = optimset('Algorithm','sqp','Display','off');
[x,fval] = ... 
fmincon(@objfun_alpha_max,x0,[],[],[],[],[],[],@confun_alpha,options);
min_alpha = fval;


%% make V_inner_local (or global based on how big X_k is)
v_lb = max_alpha+params.c4*mnu;
v_ub = min_alpha+params.c4*mxu;
V_inner_local = Polyhedron('lb',v_lb,'ub',v_ub);