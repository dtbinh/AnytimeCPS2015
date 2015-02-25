folder = '../../Data/Barrel';
load([folder,'/BarrelMasks.mat'])
images = dir([folder,'/*.png']);

load('GMs.mat');

% pixels of interest (poi)
poi = [];
nonpoi = [];
k = 1 ;
nonk = 1;

% Cluster the data (for now, not doing cross-validation)
featuresPosClass = [];
featuresNegClass = [];
minAcceptanceProbScalingFactor = 0.8;
minSignificanceProb = 0.2;
mp = 1;
mn = 1;
for m=1:nbimages
    minAcceptanceProb = minAcceptanceProb/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
    Im=imread(images(m).name);
    I = preprocess_img(Im);
    I = I(:,:,colors);
    a=size(I);
    candidate = reshape(I,a(1)*a(2),nbcolors);
    [idxpoi, ~, posteriorspoi] = cluster(poiGM,double(candidate));
    [idxnon, ~, posteriorsnon] = cluster(nonpoiGM,double(candidate));
    b = size(candidate);
    % For each pix, decide if it's best described by poi or non
    d1 = sum(posteriorspoi.*repmat(poiGM.ComponentProportion,b(1),1),2);
    d2 = sum(posteriorsnon.*repmat(nonpoiGM.ComponentProportion,b(1),1),2);
    clusterObjOfInterest = 0; %initialize while
    while (nnz(clusterObjOfInterest)==0 && minAcceptanceProb >= minSignificanceProb)
        minAcceptanceProb = minAcceptanceProb*minAcceptanceProbScalingFactor;
        clusterObjOfInterest = (d1 > max(d2,minAcceptanceProb));
    end
    minAcceptanceProb
    % Filter out the smaller things
    %...??
    % Extract features for the positive class, i.e. of barrel objects.    
    M = reshape(clusterObjOfInterest,a(1),a(2));
    statsPosClass = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid', 'Boundingbox');
    nbFoundObjects = length(statsPosClass);    
    if ~isempty(statsPosClass)        
        % Vector = major, minor, ecc, solidity
        % !! Watch out for order of entries in array returned by
        % struct2array!!!
        featurePosClass = zeros(nbFoundObjects, 3);
        for i=1:nbFoundObjects
            featurePosClass(i,:) = [statsPosClass(i).MajorAxisLength/statsPosClass(i).MinorAxisLength, statsPosClass(i).Eccentricity, statsPosClass(i).Solidity];
        end        
        [label,score]=predict(SVMModel, featurePosClass);
        % Discard low-scoring objects
        % ..??
        selectedObj = statsPosClass(label==1); % 1 is the positive class index
        imshow(Im(:,:,1));
        hold on
        centroids = cat(1, selectedObj.Centroid);
        plot(centroids(:,1), centroids(:,2), 'b*')
    end
    
end


1;
