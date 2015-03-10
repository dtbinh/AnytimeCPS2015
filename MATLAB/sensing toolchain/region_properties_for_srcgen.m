function stats = region_properties_for_srcgen(L)
% stats: n-by-6, each row contains 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid',
% of the kth component in labeled image L. Centroid is 2D

% By "second moments", the documentation means the second central moment.
% 
% In the case of one-dimensional data, this would be the variance (or square of the standard deviation).
% 
% In your case, where you have two-dimensional data, the second central moment is the covariance matrix.
% 
% If X is an n-by-2 matrix of the points in your region, you can compute the covariance matrix Sigma in MATLAB like this (untested):
% 
% mu=mean(X,1);
% X_minus_mu=X-repmat(mu, size(X,1), 1);
% Sigma=(X_minus_mu'*X_minus_mu)/size(X,1);
% Now, what does this have to do with ellipses? Well, what you're doing here is, in effect, fitting a multivariate normal distribution to your data. The covariance matrix determines the shape of that distribution, 
% and the contour lines of a multivariate normal distribution -- wait for it -- are ellipses!
% 
% The directions and lengths of the ellipse's axes are given by the eigenvectors and eigenvalues of the covariance matrix:
% 
% [V, D]=eig(Sigma);
% The columns of V are now the eigenvectors (i.e. the directions of the axes), and values on the diagonal of D are the eigenvalues (i.e. the lengths of the axes). So you already have the 'MajorAxisLength' and 'MinorAxisLength'. 
% The orientation is probably just the angle between the major axis and the horizontal (hint: use atan2 to compute this from the vector pointing along the major axis). 
%
%Finally, the eccentricity is
% 
% sqrt(1-(b/a)^2)
% where a is the length of the major axis and b is the length of the minor axis.

nbregions = max(max(L));
stats = complex(zeros(nbregions,6));
for n=1:nbregions
    ff = find(L==n);
    [I,J] = ind2sub(size(L),ff);
    X = [I,J];    
    mu = mean(X,1);
    X_minus_mu = X - repmat(mu, size(X,1), 1);
    Sigma=(X_minus_mu'*X_minus_mu)/size(X,1);
    D = eig(Sigma);
    MajorAxisLength = max(D);
    MinorAxisLength = min(D);
    assert(MajorAxisLength > 0);
    assert(MinorAxisLength >= 0);
    Eccentricity = sqrt(1-(MinorAxisLength/MajorAxisLength)^2);
    Area = length(ff);
    Centroid = sum(X)./Area;
    stats(n,1) = MajorAxisLength;
    stats(n,2) = MinorAxisLength;
    stats(n,3) = Eccentricity;
    stats(n,4) = 1;
    stats(n,5:6) = Centroid;    
end
