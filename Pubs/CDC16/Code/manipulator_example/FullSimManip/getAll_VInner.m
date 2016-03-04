function V_inner_jgk = getAll_VInner(X_reach,U,N,params)

%X_reach is a set of reachable Polyhedrons from time k (incl.) onwards,
%indexed from 1 to N+1, in cell format

%%
V_inner_jgk = cell(N+1,1);
% do computations
for i = 1:N+1
   
    V_inner_jgk{i} = getLocalVInner_interval(X_reach{i},U,params);

end