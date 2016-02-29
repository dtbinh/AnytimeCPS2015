function fval = obj_set_max_x3(z)
load('SetsAndParams.mat');
fval = -((1/params.c2)*(z(3) + params.c1*sin(z(1)) + params.c2*z(1)));