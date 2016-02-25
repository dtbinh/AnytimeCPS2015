function [S_rect,maxs,mins] = getRect(S)
%% get rectangle bounding a set S in R^n
printonce = 1;
[~,n] = size(S.A);
maxs = zeros(n,1);
mins = zeros(n,1);
for i = 1:n
    for j = 1:2 %max and min
        c = ((-1)^j);
        cvx_begin quiet
        if(exist('gurobi'))
            cvx_solver gurobi;
        end
        if(exist('gurobi') && exist('yalmip') && printonce)
            'Truong would be proud of this setup'
            printonce = 0;
        end
        
        variable x(n)
        
        minimize c*x(i)
        subject to
        
        S.A*x<=S.b;
        
        cvx_end
        if(j==1)
            maxs(i) = x(i);
        else
            mins(i) = x(i);
        end
        cvx_clear;
    end
end


Amatrix = [eye(n);-eye(n)];
bvector = [maxs;-mins];
S_rect = Polyhedron('A',Amatrix,'b',bvector);
S_rect.minHRep;
