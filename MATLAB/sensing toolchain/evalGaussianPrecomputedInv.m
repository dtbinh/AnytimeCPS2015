function g = evalGaussianPrecomputedInv(data,mu,invsigma)
D = length(mu);
ndata = size(data,1);
data = data - repmat(mu,ndata,1);
g = zeros(ndata,1);
for j=1:ndata
    x = data(j,:);
    g(j) = exp(-0.5*(x*invsigma)*x');
end
g = ((0.5/pi)^(0.5*D))*sqrt(det(invsigma))*g;
end