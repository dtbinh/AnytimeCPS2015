function [elapsedtime, estimationError] = run_perception_module(inImgName, GMs, mask, nbfeatures)
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
SVMModel                        = GMs.SVMModel;


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
clusterObjOfInterest = 0; %initialize while
while (nnz(clusterObjOfInterest)==0 && minAcceptanceProb >= minSignificanceProb)
    minAcceptanceProb = minAcceptanceProb*minAcceptanceProbScalingFactor;
    clusterObjOfInterest = (d1 > max(d2,minAcceptanceProb));
end
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
    if nbfeatures ==1
    [label,score]=predict(SVMModel, featuresPosClass(:,3));
    else
    [label,score]=predict(SVMModel, featuresPosClass);
     end
 
    % Keep positively classified objects with high enough scores.
    % score(:,2) is a column of positive class scores = posterior
    % probabilities. For this to work, the SVMModel must have been passed
    % through fitSVMposterior.
    % If we know only one OOI is in the image, can choose the best-scoring
    % object...
    candidateObj = statsPosClass(label==1); % 1 is the positive class index
    [~,mix] = max(score(label==1,2));
    selectedObj = candidateObj(mix);   
    
    elapsedtime = toc;
    
    % Error of estimatino toolchain is distance between true centroid and
    % estimated centroid
    centroid = cat(1, selectedObj.Centroid);
    dasprops = regionprops(mask,'Centroid');
    estimationError=norm(centroid - dasprops.Centroid);
%             figure
%             imshow(Im(:,:,1));
%             hold on            
%             plot(centroid(:,1), centroid(:,2), 'b*')
%             plot(dasprops.Centroid(:,1), dasprops.Centroid(:,2), 'r*')
end




end
