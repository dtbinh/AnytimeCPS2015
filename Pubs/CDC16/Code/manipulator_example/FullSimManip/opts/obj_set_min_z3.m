function fval = obj_set_min_z3(x)
load('SetsAndParams.mat');
fval = (-params.c1*sin(x(1))-params.c2*(x(1)-x(3)));

