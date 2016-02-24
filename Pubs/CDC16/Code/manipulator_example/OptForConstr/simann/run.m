%[xopt]=simann('gp', [1,2], [-2,-2], [2,2], 1000, .5, 5, 20, 100)
%feval('gp',xopt)
%x0 = zeros(4,1);
[xopt] = simann('objfun',x0,-1*[pi/2;pi/2;pi/4;pi/3],[pi/2;pi/2;pi/4;pi/3], ...
    1000,.5,5,20,100);
fopt_simann = feval('objfun',xopt)
