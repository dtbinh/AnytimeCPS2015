function run_perception_module_for_srcgen(Im, colors, minAcceptanceProbScalingFactor, minSignificanceProb, minAcceptanceProb, ...
    muPOI, SigmaPOI, ComponentProportionPOI, ...
    muNON, SigmaNON, ComponentProportionNON, ...
    Alpha, SupportVectorLabels, KernelScale, SupportVectors, Bias)

nbcolors    = length(colors);
nbcomponents = size(ComponentProportionPOI,2);

% Detect pix of interest
minAcceptanceProb = minAcceptanceProb/minAcceptanceProbScalingFactor; % allow for 1st iteration of while loop
I = preprocess_img(Im);
I = I(:,:,colors);
a=size(I);
candidate = reshape(I,a(1)*a(2),nbcolors);


posteriorspoi = posteriors_for_srcgen(muPOI,SigmaPOI,ComponentProportionPOI, candidate);
posteriorsnon = posteriors_for_srcgen(muNON,SigmaNON,ComponentProportionNON, candidate);

b = size(candidate);
% For each pix, decide if it's best described by poi or non
d1 = sum(posteriorspoi.*repmat(ComponentProportionPOI,b(1),1),2);
d2 = sum(posteriorsnon.*repmat(ComponentProportionNON,b(1),1),2);
clusterObjOfInterest = false(b(1),1); %initialize while
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

% Detect shapes
if ~isempty(statsPosClass)
    % Vector = major, minor, ecc, solidity
    featuresPosClass = zeros(nbFoundObjects, 3);
    for i=1:nbFoundObjects
        featuresPosClass(i,:) = [statsPosClass(i).MajorAxisLength/statsPosClass(i).MinorAxisLength, statsPosClass(i).Eccentricity, statsPosClass(i).Solidity];
    end
    label = svmpredict_for_srcgen(featuresPosClass, Alpha, SupportVectorLabels, KernelScale, SupportVectors, Bias);
    
    % Discard low-scoring objects
    % ..??
    
    selectedObj = statsPosClass(label==1); % 1 is the positive class index
%                 figure
%                 imshow(Im(:,:,1));
%                 hold on
%                 centroids = cat(1, selectedObj.Centroid);
%                 plot(centroids(:,1), centroids(:,2), 'b*')
end


end