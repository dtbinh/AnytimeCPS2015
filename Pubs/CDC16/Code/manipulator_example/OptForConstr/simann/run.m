%[xopt]=simann('gp', [1,2], [-2,-2], [2,2], 1000, .5, 5, 20, 100)
%feval('gp',xopt)
%x0 = zeros(4,1);
[xopt] = simann('obj_set_min_z3',x0,-1*[pi/2;pi/2;pi/4;pi/3],[pi/2;pi/2;pi/4;pi/3], ...
    1000,.5,5,20,100);
fopt_simann = feval('obj_set_min_z3',xopt)
