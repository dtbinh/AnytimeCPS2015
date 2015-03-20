function run_perception_module(inImgName)
% run_perception_module(inImgName)
% 
% Run the perception tool chain on input image whose name is inImgName
%

%folder = '../../Data/Barrel';
%images = dir([folder,'/*.png']);
GMs = load('trainedPerception.mat');
knobs       = GMs.knobs;
colors      = knobs.colors;
nbcolors    = length(colors);
poiGM       = GMs.poiGM;
nonpoiGM    = GMs.nonpoiGM;
minAcceptanceProbScalingFactor 	= knobs.minAcceptanceProbScalingFactor;
minSignificanceProb             = knobs.minSignificanceProb;
minInitialAcceptanceProb               = knobs.minInitialAcceptanceProb;
SVMModel                        = GMs.SVMModel;


% Cluster the data
minAcceptanceProb = minInitialAcceptanceProb/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
Im=imread(inImgName);
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
% Filter out the smaller things
M = imerode(reshape(clusterObjOfInterest,a(1),a(2)),strel('rectangle',[1,1]));
M = medfilt2(M,'symmetric');
% Connect components and extract features for the positive class, i.e. of barrel objects.
statsPosClass = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid', 'Boundingbox');
nbFoundObjects = length(statsPosClass);
if ~isempty(statsPosClass)
    % Vector = major, minor, ecc, solidity
    featuresPosClass = zeros(nbFoundObjects, 3);
    for i=1:nbFoundObjects
        featuresPosClass(i,:) = [statsPosClass(i).MajorAxisLength/statsPosClass(i).MinorAxisLength, statsPosClass(i).Eccentricity, statsPosClass(i).Solidity];
    end
    if isa(SVMModel, 'classreg.learning.partition.ClassificationPartitionedModel')
    [label,score]=kfoldPredict(SVMModel, featuresPosClass);    
    else
    end
    [label,score]=predict(SVMModel, featuresPosClass);
    % Discard low-scoring objects
    % ..??
    selectedObj = statsPosClass(label==1); % 1 is the positive class index
%             figure
%             imshow(Im(:,:,1));
%             hold on
            centroids = cat(1, selectedObj.Centroid);
            plot(centroids(:,1), centroids(:,2), 'b*')
end




end