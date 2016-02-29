function fval = obj_set_max_x4(z)
load('SetsAndParams.mat');
fval = -((1/params.c2)*(z(4) + params.c2*z(2)*cos(z(1)) + params.c2*z(2)));