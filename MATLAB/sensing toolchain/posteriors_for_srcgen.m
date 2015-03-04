function post = posteriors_for_srcgen(mu, Sigma, ComponentProportion, data)
% Compute the posterior probability of each row in data (M-by-N) in
% the GMM with mean mu (K-by-N), variance Sigma (N-by-N-by-K), and
% mixing proportions ComponentProportion (1-by-K).
% N is the space dimension, K is the nb of components in the GMM, M is the
% nb of data points.
%
% There's room for improving run speed here.

nbcomponents = size(mu,1);
M = size(data,1);
den = zeros(M,1);
likelihood = zeros(M,nbcomponents);
for k=1:nbcomponents
%     likelihood2(:,k) =  mvnpdf(data, mu(k,:),Sigma(:,:,k));
%     likelihood(:,k) = evalGaussian(data,mu(k,:), Sigma(:,:,k));
    invVariance = inv(Sigma(:,:,k));
    likelihood(:,k) = evalGaussianPrecomputedInv(data,mu(k,:), invVariance);
%     nnz(abs(likelihood(:,k)-likelihood2(:,k)))
%     max(abs(likelihood(:,k)-likelihood2(:,k)))
    den = den + ComponentProportion(k)*likelihood(:,k);
end
num = likelihood.*repmat(ComponentProportion,M,1);
post = num./repmat(den,1,nbcomponents);
 




end