function E_tilde_jgk = getAll_E_tilde(X_reach,E,N,params)

%X_reach is a set of reachable Polyhedrons from time k (incl.) onwards,
%indexed from 1 to N+1, in cell format

%%
E_tilde_jgk = cell(N+1,1);

for i = 1:N+1
   
    E_tilde_jgk{i} = get_E_tilde_bound(X_reach{i},E,params);
    
end
