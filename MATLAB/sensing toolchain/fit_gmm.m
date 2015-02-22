folder = '../../Data/Barrel';
load([folder,'/BarrelMasks.mat'])
images = dir([folder,'/*.png']);
% pixels of interest (poi)
poi = []; 
nonpoi = [];
% we may choose to fit one, two or all three color components.
colors = 1;
nbcolors = length(colors);
nbcomponentsPOI = 1;
nbcomponentsNonPOI = 1; 
nbimages = 10 %length(images)
k = 1 ;
nonk = 1;
for m=1:nbimages
    M=bw(:,:,m);
    I=imread(images(m).name);
    a = size(I);
    % Normalize to decrease sensitivity to lighting variations
    I = double(I)./repmat(sum(I,3),1,1,3);
    a=size(I);
    
    N=nnz(M);   
    % Add pois of the new image    
    poi = [poi; zeros(N,nbcolors)];
    linear = find(M);
    for c=1:nbcolors
        Ic = I(:,:,colors(c));
        poi(k:end,c) = Ic(linear);
    end
    k = size(poi,1)+1;
    
    % Add non-pois as well - trying to work around ill-conditioning
    nonpoi = [nonpoi; zeros(a(1)*a(2) - N,nbcolors)];
    linear = find(~M);
    for c=1:nbcolors
        Ic = I(:,:,c);
        nonpoi(nonk:end,c) = Ic(linear);
    end
    nonk = size(nonpoi,1)+1;
    % ---------------------------
    % poi = [poi; reshape(I,a(1)*a(2),3)];
    % ---------------------------
end
tic
poiGM = fitgmdist(poi,nbcomponentsPOI);
toc
if ~poiGM.Converged
    warning('Did not converge')
end
tic
nonpoiGM = fitgmdist(nonpoi,nbcomponentsNonPOI);
toc
if ~nonpoiGM.Converged
    warning('non POI Did not converge')
end

% Create combined gmm
allsigma(:,:,1) = poiGM.Sigma;
allsigma(:,:,2) = nonpoiGM.Sigma;
% ?? How to determine the mixture weights
allgm=gmdistribution([poiGM.mu;nonpoiGM.mu],allsigma,[0.3 0.7]);
idxObjectOfInterest = 1;

% Cluster the data (for now, not doing cross-validation)
for m=1:nbimages
    I=imread(images(m).name);
    I = I(:,:,colors);
    a=size(I);
    candidate = reshape(I,a(1)*a(2),nbcolors);
    [idx, ~, posteriors] = cluster(allgm,double(candidate));
    clusterObjOfInterest = (idx == idxObjectOfInterest);
end

% Extract features for the positive class, i.e. of barrel objects.
for m=1:nbimages
    M=bw(:,:,m);
    stats(m) = regionprops(M,'BoundingBox', 'ConvexHull', 'Eccentricity', 'MajorAxisLength', 'MinorAxisLength', 'Solidity');
end
% Now extract features from negative class, i.e. non-barrel objects

