function [lb,ub] = getOuterRect(M,mu)
%outer rectangular approx for ellipsoid 
% (x-mu)'M(x-mu)<=1
if(nargin<1)
    M = eye(3);
    mu = zeros(3,1);
end
if(nargin==1)
   mu = zeros(length(M),1); 
end   

%%
%M = eye(3);
%mu = zeros(length(M),1);
ub = zeros(length(M),1);
lb = zeros(length(M),1);
p = length(M);
for i = 1:p
    for j = 1:2
    cvx_clear    
    cvx_begin quiet
    variable x(p)
    minimize(((-1)^j)*x(i))
    subject to
    (x-mu)'*M*(x-mu)<=1;     
    cvx_end 
    if(j==1)
        ub(i) = x(i);
    else
        lb(i) = x(i);
    end
    end
end