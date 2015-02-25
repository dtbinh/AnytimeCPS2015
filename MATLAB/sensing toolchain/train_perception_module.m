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
nbcomponentsNonPOI = 4;
nbimages = 3 %#ok<NOPTS> %length(images)
k = 1 ;
nonk = 1;
if ~exist('loadgmm', 'var') ||  ~loadgmm
    for m=1:nbimages
        M=bw(:,:,m);
        Im=imread(images(m).name);
        % Normalize to decrease sensitivity to lighting variations
        I = preprocess_img(Im);
        a=size(I);
        %----------------------------
        % Approach 1: classify gmm on entire image, find a way to get the
        % component for the object of interest later
        % poi = [poi; reshape(I(:,:,colors),a(1)*a(2),nbcolors)];
        % ---------------------------
        % Approach 2: classify poi and nonpoi separately
        N=nnz(M);
        % Add pois of the new image
        poi = [poi; zeros(N,nbcolors)];
        linear = find(M==1);
        for c=1:nbcolors
            Ic = I(:,:,colors(c));
            poi(k:end,c) = Ic(linear);
        end
        %     scatter3(poi(:,1), poi(:,2), poi(:,3)); xlabel('R'); ylabel('G'); zlabel('B')
        k = size(poi,1)+1;
        % Add non-pois as well - trying to work around ill-conditioning
        nonpoi = [nonpoi; zeros(a(1)*a(2) - N,nbcolors)];
        linear = find(M==0);
        for c=1:nbcolors
            Ic = I(:,:,c);
            nonpoi(nonk:end,c) = Ic(linear);
        end
        nonk = size(nonpoi,1)+1;
    end
    regularizationValue = 0.01;
    tic
    poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
    % poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'plus');
    toc
    if ~poiGM.Converged
        warning('Did not converge')
    end
    tic
    nonpoiGM = fitgmdist(nonpoi,nbcomponentsNonPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
    % nonpoiGM = fitgmdist(nonpoi,nbcomponentsNonPOI, 'Start', 'plus');
    toc
    if ~nonpoiGM.Converged
        warning('non POI Did not converge')
    end
    save('GMs.mat', 'poiGM', 'nonpoiGM');
else
    load('GMs.mat');
end

% Cluster the data (for now, not doing cross-validation)
featuresPosClass = [];
featuresNegClass = [];
minAcceptanceProbScalingFactor = 0.8;
minSignificanceProb = 0.2;
mp = 1;
mn = 1;
for m=1:nbimages
    minAcceptanceProb = 0.5/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
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
    %...
    % Extract features for the positive class, i.e. of barrel objects.
    % We can either use the fact that we have manually extracted this
    % object...
    % M=bw(:,:,m);
    % ...or pick it from the gmm
    M = reshape(clusterObjOfInterest,a(1),a(2));
    statsPosClass = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity');
    nbFoundObjects = length(statsPosClass);
    if ~isempty(statsPosClass)
        % Vector = major, minor, ecc, solidity
        featureVector = reshape(struct2array(statsPosClass),4,nbFoundObjects)';
        featuresPosClass(mp:mp+nbFoundObjects-1,:) = [featureVector(:,1)./featureVector(:,2), featureVector(:,3:4)];
        mp = mp + nbFoundObjects;
    end
    % Extract features for the negative class
    % currently the only way to do so is by using the stuff detected as
    % being of class OOI (as determined by a thresholding on d1), but isn't
    % (as determined by clusterObjOfInterest)
    M = reshape((d1 > minSignificanceProb).*(~clusterObjOfInterest),a(1),a(2));
    statsNegClass = regionprops(M, 'Eccentricity', 'MajorAxisLength', 'MinorAxisLength', 'Solidity');
    nbFoundObjects = length(statsNegClass);
    if ~isempty(statsNegClass)
        % Vector = major, minor, ecc, solidity
        featureVector = reshape(struct2array(statsNegClass),4,nbFoundObjects)';
        featuresNegClass(mn:mn+nbFoundObjects-1,:) = [featureVector(:,1)./featureVector(:,2), featureVector(:,3:4)];
        mn = mn + nbFoundObjects;
    end
end
% Now train the SVM
SVMModel = fitcsvm([featuresNegClass; featuresPosClass],[-ones(size(featuresNegClass,1),1); ones(size(featuresPosClass,1),1)],...
    'KernelFunction','rbf','Standardize',true, ...
    'PredictorNames', {'majorByMinor', 'eccentricity', 'solidity'});

save('GMs.mat', 'poiGM', 'nonpoiGM', 'SVMModel', 'colors', 'minAcceptanceProb', 'minAcceptanceProbScalingFactor', 'minSignificanceProb', 'nbcolors', 'nbcomponentsPOI', 'nbcomponentsNonPOI', 'nbimages');

1;
