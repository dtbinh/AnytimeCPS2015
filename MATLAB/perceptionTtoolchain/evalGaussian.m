function g = evalGaussian(data,mu,sigma)
D = length(mu);
ndata = size(data,1);
data = data - repmat(mu,ndata,1);
g = zeros(ndata,1);
for j=1:ndata
    x = data(j,:);
    exponent = -0.5*(x/sigma);
    exponent = exponent*x';
    g(j) = exp(exponent);
end
g = ((0.5/pi)^(0.5*D))*sqrt(1/det(sigma))*g;
end