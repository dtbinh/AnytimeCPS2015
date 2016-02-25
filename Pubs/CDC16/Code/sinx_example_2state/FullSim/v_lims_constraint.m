function [c,ceq] = v_lims_constraint(x)
load('Data/vlims_data.mat');
ceq = [];
maxs = zeros(3,1);
mins = zeros(3,1);
[~,maxs(1:2),mins(1:2)] = getRect(X_k);
[~,maxs(3),mins(3)] = getRect(U);
c = [x(1)-maxs(1);
    -x(1)+mins(1);
    x(2)-maxs(2);
    -x(2)+mins(2);
    x(3)-maxs(3);
    -x(3)+mins(3)];