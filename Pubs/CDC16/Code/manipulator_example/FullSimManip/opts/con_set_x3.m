function [c,ceq] = con_set_x3(z)
load('SetsAndParams.mat');
ceq = [];
c = zset.A*z-zset.b;
