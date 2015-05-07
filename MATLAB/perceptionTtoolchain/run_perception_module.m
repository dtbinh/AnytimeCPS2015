function [elapsedtime, estimationError, frisempty] = run_perception_module(inImgName, GMs, mask, nbfeatures, shape_classifier)
% run_perception_module(inImgName)
%
% Run the perception tool chain on input image whose name is inImgName
%
knobs       = GMs.knobs;
colors      = knobs.colors;
nbcolors    = length(colors);
poiGM       = GMs.poiGM;
nonpoiGM    = GMs.nonpoiGM;
minAcceptanceProbScalingFactor 	= knobs.minAcceptanceProbScalingFactor;
minSignificanceProb             = knobs.minSignificanceProb;
minInitialAcceptanceProb        = knobs.minInitialAcceptanceProb;


frisempty = 0;

% Cluster the data
minAcceptanceProb = minInitialAcceptanceProb/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
Im=imread(inImgName);

tic

I = preprocess_img(Im);
I = I(:,:,colors);
a=size(I);
candidate = reshape(I,a(1)*a(2),nbcolors);
[~, ~, posteriorspoi] = cluster(poiGM,double(candidate));
[~, ~, posteriorsnon] = cluster(nonpoiGM,double(candidate));
b = size(candidate);
% For each pix, decide if it's best described by poi or non
d1 = sum(posteriorspoi.*repmat(poiGM.PComponents,b(1),1),2);
d2 = sum(posteriorsnon.*repmat(nonpoiGM.PComponents,b(1),1),2);
clusterObjOfInterest = cluster_with_gmm(d1,d2,minAcceptanceProb,minSignificanceProb,minAcceptanceProbScalingFactor);                
% Filter out the smaller things
M = imerode(reshape(clusterObjOfInterest,a(1),a(2)),strel('rectangle',[1,1]));
M = medfilt2(M,'symmetric');
% Connect components and extract features for the positive class, i.e. of barrel objects.
statsPosClass = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid');
nbFoundObjects = length(statsPosClass);
if ~isempty(statsPosClass)
    % Vector = major, minor, ecc, solidity
    featuresPosClass = zeros(nbFoundObjects, 3);
    for i=1:nbFoundObjects
        featuresPosClass(i,:) = [statsPosClass(i).MajorAxisLength/statsPosClass(i).MinorAxisLength, statsPosClass(i).Eccentricity, statsPosClass(i).Solidity];
    end
    if nbfeatures == 1
        feats =  featuresPosClass(:,3);
    else
        feats =  featuresPosClass;
    end
    if strcmp(shape_classifier, 'SVM')       
        SVMModel                        = GMs.SVMModel;
        [label,score]=predict(SVMModel, feats);  
        score = score(:,2);
    elseif strcmp(shape_classifier, 'GMM')     
        shapePosGM = GMs.shapePosGM;
        shapeNegGM = GMs.shapeNegGM;
        [~, ~, posteriorspoi] = cluster(shapePosGM,feats);
        [~, ~, posteriorsnon] = cluster(shapeNegGM,feats);
        b = size(feats);
        % For each pix, decide if it's best described by poi or non
        % The di's give posterior probabilities
        d1 = sum(posteriorspoi.*repmat(shapePosGM.PComponents,b(1),1),2);
        d2 = sum(posteriorsnon.*repmat(shapeNegGM.PComponents,b(1),1),2);
        % label == 1 means it's best explained by shapePosGM (i.e., it
        % belongs to an OOI)
        label = cluster_with_gmm(d1,d2,0.5,0.2,0.8);
        % To keep this homogeneous with SVM case, create a score matrix
        % which in this case gives the posterior assigned to each object by
        % the GMM that best explains it
        score = d1.*label + d2.*(~label);        
    else
        error('not a known shape classifier')
    end
       
    
    % Keep positively classified objects with high enough scores.
    % score(:,2) is a column of positive class scores = posterior
    % probabilities. For this to work, the SVMModel must have been passed
    % through fitSVMposterior.
    % If we know only one OOI is in the image, can choose the best-scoring
    % object...
    candidateObj = statsPosClass(label==1); % 1 is the positive class index
    % 
    if ~isempty(candidateObj)
        [~,mix] = max(score(label==1));
        selectedObj = candidateObj(mix);
        
        elapsedtime = toc;
        
        % Error of estimatino toolchain is distance between true centroid and
        % estimated centroid
        centroid = cat(1, selectedObj.Centroid);
        dasprops = regionprops(mask,'Centroid');
        truecentroid = dasprops.Centroid;
        estimationError=norm(centroid - truecentroid);
        figure
        imshow(Im(:,:,1));
        hold on
        plot(centroid(:,1), centroid(:,2), 'b*')
        plot(truecentroid(:,1), truecentroid(:,2), 'r*')
        1;
    else
        warning('Did not find an OOI');
        elapsedtime = inf;
        estimationError = inf;
        frisempty = frisempty + 1;
    end
else
	warning('Did not find any POIs');
	frisempty = frisempty + 1;
	elapsedtime = inf;
	estimationError = inf;
end




end
