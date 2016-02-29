function fval = obj_set_min_z4(x)
load('SetsAndParams.mat');
fval =  -params.c1*x(2)*cos(x(1)) - params.c2*(x(2)-x(4));
