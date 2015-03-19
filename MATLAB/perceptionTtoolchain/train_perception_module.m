folder = '../../Data/Barrel';
addpath(folder);
load([folder,'/BarrelMasks.mat'])
images = dir([folder,'/*.png']);

% Knobs to control the perception tool chain
knobs.nbimages = 3;
knobs.colors = [1 2 3];
knobs.nbcomponentsPOI = 4;
knobs.nbcomponentsNonPOI = 4;
knobs.minInitialAcceptanceProb = 0.5;
knobs.minAcceptanceProbScalingFactor = 0.8;
knobs.minSignificanceProb = 0.2;
knobs.featuresList = {'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity'};
knobs.nbValidationFolds = 5;

% pixels of interest (poi)
poi = [];
nonpoi = [];
% we may choose to fit one, two or all three color components.
colors = knobs.colors;
nbcolors = length(colors);
nbcomponentsPOI = knobs.nbcomponentsPOI;
nbcomponentsNonPOI = knobs.nbcomponentsNonPOI;
nbimages = knobs.nbimages %#ok<NOPTS> %length(images)
 
k = 1 ;
nonk = 1;
if ~exist('loadgmm', 'var') ||  ~loadgmm
    for m=1:nbimages
        M=bw(:,:,m);
        Im=imread(images(m).name);        
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
        % Add non-pois as well
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
    poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'randSample', 'Regularize',regularizationValue);
    %poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
    if ~poiGM.Converged
        warning('Did not converge')
    end
    nonpoiGM = fitgmdist(nonpoi,nbcomponentsNonPOI, 'Start', 'randSample', 'Regularize',regularizationValue);
    %nonpoiGM = fitgmdist(nonpoi,nbcomponentsPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
    if ~nonpoiGM.Converged
        warning('non POI Did not converge')
    end
    save('GMs.mat', 'poiGM', 'nonpoiGM');
else
    load('GMs.mat');
end

% Cluster the data
featuresPosClass = [];
featuresNegClass = [];
minAcceptanceProbScalingFactor = knobs.minAcceptanceProbScalingFactor ;
minSignificanceProb = knobs.minSignificanceProb ;
minInitialAcceptanceProb = knobs.minInitialAcceptanceProb ;
mp = 1;
mn = 1;
for m=1:nbimages
    minAcceptanceProb = minInitialAcceptanceProb/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
    Im=imread(images(m).name);
    I = preprocess_img(Im);
    I = I(:,:,colors);
    a=size(I);
    candidate = reshape(I,a(1)*a(2),nbcolors);
    [idxpoi, ~, posteriorspoi] = cluster(poiGM,double(candidate));
    [idxnon, ~, posteriorsnon] = cluster(nonpoiGM,double(candidate));
    b = size(candidate);
    % For each pix, decide if it's best described by poi or non
    d1 = sum(posteriorspoi.*repmat(poiGM.PComponents,b(1),1),2);
    d2 = sum(posteriorsnon.*repmat(nonpoiGM.PComponents,b(1),1),2);
    clusterObjOfInterest = 0; %initialize while
    while (nnz(clusterObjOfInterest)==0 && minAcceptanceProb >= minSignificanceProb)
        minAcceptanceProb = minAcceptanceProb*minAcceptanceProbScalingFactor;
        clusterObjOfInterest = (d1 > max(d2,minAcceptanceProb));
    end
    %minAcceptanceProb
    % Filter out the smaller things
    M = imerode(reshape(clusterObjOfInterest,a(1),a(2)),strel('rectangle',[1,1]));
    M = medfilt2(M,'symmetric');
    % Extract features for the positive class, i.e. of barrel objects.
    % We can either use the fact that we have manually extracted this
    % object...
    % M=bw(:,:,m);
    % ...or pick it from the gmm   
    featuresList = knobs.featuresList;
    statsPosClass = regionprops(M, featuresList{1}, featuresList{2}, featuresList{3} , featuresList{4});
%     statsPosClass = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity');
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
    statsNegClass = regionprops(M, featuresList{1}, featuresList{2}, featuresList{3} , featuresList{4});
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
    'Crossval', 'on', 'KFold', knobs.nbValidationFolds, ...
    'PredictorNames', {'majorByMinor', 'eccentricity', 'solidity'});

save('tempGMs.mat', 'poiGM', 'nonpoiGM', 'SVMModel', 'knobs');

1;
