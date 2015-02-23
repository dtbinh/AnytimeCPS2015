folder = '../../Data/Barrel';
load([folder,'/BarrelMasks.mat'])
images = dir([folder,'/*.png']);
% pixels of interest (poi)
poi = []; 
nonpoi = [];
% we may choose to fit one, two or all three color components.
colors = [1 2 3];
nbcolors = length(colors);
nbcomponentsPOI = 4;
nbcomponentsNonPOI = 1; 
nbimages = 10 %#ok<NOPTS> %length(images)
k = 1 ;
nonk = 1;
for m=1:nbimages
    M=bw(:,:,m);
    I=imread(images(m).name);
    % Normalize to decrease sensitivity to lighting variations
    I = double(I)./repmat(sum(I,3),1,1,3);
    a=size(I);
    
    % Approach 1: classify gmm on entire image, find a way to get the
    % component for the object of interest later
    
    N=nnz(M);   
    % Add pois of the new image    
    poi = [poi; zeros(N,nbcolors)];
    linear = find(M==1);
    for c=1:nbcolors
        Ic = I(:,:,colors(c));
        poi(k:end,c) = Ic(linear);
    end
    k = size(poi,1)+1;
    
    % Add non-pois as well - trying to work around ill-conditioning
    nonpoi = [nonpoi; zeros(a(1)*a(2) - N,nbcolors)];
    linear = find(M==0);
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
featuresPosClass = zeros(nbimages,3);
featuresNegClass = zeros(nbimages,3);
for m=1:nbimages
    I=imread(images(m).name);
    I = I(:,:,colors);
    a=size(I);
    candidate = reshape(I,a(1)*a(2),nbcolors);
    [idx, ~, posteriors] = cluster(allgm,double(candidate));
    % Extract features for the positive class, i.e. of barrel objects.
    % We can either use the fact that we have manually extracted this
    % object...
    % M=bw(:,:,m); 
    % ...or pick it from the gmm
    clusterObjOfInterest = (idx == idxObjectOfInterest);    
    M = reshape(clusterObjOfInterest,a(1),a(2));
    statsPosClass = regionprops(M, 'Eccentricity', 'MajorAxisLength', 'MinorAxisLength', 'Solidity');
    featuresPosClass(m,:) = [statsPosClass.MajorAxisLength/statsPosClass.MinorAxisLength, statsPosClass.Eccentricity, statsPosClass.Solidity];
    % Extract features for the negative class
    % We can either pick random non-object contiguous sections from the mask...
%     nM = zeros(size(M));
    
    % ... or we can use the non-ooi objects picked by the processing so
    % far
    clusterOthers = (idx ~= idxObjectOfInterest);
    M = reshape(clusterOthers,a(1),a(2));
    statsNegClass = regionprops(M, 'Eccentricity', 'MajorAxisLength', 'MinorAxisLength', 'Solidity');
    featuresNegClass(m,:) = [statsNegClass.MajorAxisLength/statsNegClass.MinorAxisLength, statsNegClass.Eccentricity, statsNegClass.Solidity];    
end
% Now train the SVM
SVMModel = fitcsvm([featuresNegClass; featuresPosClass],[-ones(size(featuresNegClass,1),1); ones(size(featuresPosClass,1),1)],'KernelFunction','rbf','Standardize',true,'ClassNames',{'negClass','posClass'});


1;
