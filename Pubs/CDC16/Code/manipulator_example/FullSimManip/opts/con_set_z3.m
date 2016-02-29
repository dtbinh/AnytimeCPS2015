function [c,ceq] = con_set_z3(x)
load('SetsAndParams.mat');
ceq = [];
c = xset.A*x-xset.b;
