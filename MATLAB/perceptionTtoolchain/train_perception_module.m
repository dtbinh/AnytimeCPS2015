folder = '../../Data/Barrel';
addpath(folder);
load([folder,'/BarrelMasks.mat'])
images = dir([folder,'/*.png']);

% This is the god set {'1.3','1.7','1.8','1.9','2.0'};
trainingimages = [1,3,4,5,11]; 
nbimages = length(trainingimages);
% Pixel classifier knob
listPC = 6;%[4,6,8];
% Connected components knob
listNConnComp = 8;%[4,8];
% Shape calssifier knob
listShapeFeatures = 3;%[1,3];
% Pixel classifier knob
listPC = 6;%[4,6,8];
% Connected components knob
listNConnComp = 8;%[4,8];
% Shape calssifier knob
listShapeFeatures = 3;%[1,3];


for nbGMcomp=listPC
    for nbconncomp=listNConnComp
        for nbShapeFeatures = listShapeFeatures            
            nbcomponentsPOI = nbGMcomp;
            nbcomponentsNonPOI = nbGMcomp;            
            [nbcomponentsPOI, nbcomponentsNonPOI, nbconncomp, nbShapeFeatures]
            % Knobs to control the perception tool chain
            knobs.nbimages = min(length(images), nbimages);
            knobs.colors = [1 2 3];
            knobs.nbcomponentsPOI = nbcomponentsPOI;
            knobs.nbcomponentsNonPOI = nbcomponentsNonPOI;
            knobs.nbconncomp = nbconncomp;
            if nbShapeFeatures == 1
                knobs.featuresList = {'Eccentricity'};
            elseif nbShapeFeatures == 3
                knobs.featuresList = {'MajorbyMinor', 'Eccentricity', 'Solidity'};
            else
                error('nbShapeFeatures must be 1 or 3');
            end
            knobs.minAcceptanceProbScalingFactor = 0.8;
            knobs.minInitialAcceptanceProb = 0.6;
            knobs.minSignificanceProb = 0.5;
            knobs.nbValidationFolds = 5;
            
            % pixels of interest (poi)
            poi = [];
            nonpoi = [];
            % we may choose to fit one, two or all three color components.
            colors = knobs.colors;
            nbcolors = length(colors);
            
            k = 1 ;
            nonk = 1;
            if ~exist('loadgmm', 'var') ||  ~loadgmm
                datestr(now)
                for m=trainingimages
                    disp(['For GMM, processing image ',num2str(m)])
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
                disp('Training POI GMM')
                datestr(now)
                %poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'randSample', 'Regularize',regularizationValue);
                poiGM = fitgmdist(poi,nbcomponentsPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
                if ~poiGM.Converged
                    warning('POI Did not converge')
                end
                disp('Training nonpoi GMM')
                datestr(now)
                nonpoiGM = fitgmdist(nonpoi,nbcomponentsNonPOI, 'Start', 'randSample', 'Regularize',regularizationValue);
                %nonpoiGM = fitgmdist(nonpoi,nbcomponentsPOI, 'Start', 'plus', 'RegularizationValue',regularizationValue);
                if ~nonpoiGM.Converged
                    warning('non POI Did not converge')
                end
                datestr(now)
                save('GMs.mat', 'poiGM', 'nonpoiGM')
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
            for m=trainingimages
                disp(['For SVM, m=',num2str(m)])
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
                % Extract features for the positive class, i.e. of barrel objects.
                % We can either use the fact that we have manually extracted this
                % object...
                M=bw(:,:,m);                
                % ...or pick it from the gmm
                % First, filter out the smaller things
%                 M = imerode(reshape(clusterObjOfInterest,a(1),a(2)),strel('rectangle',[1,1]));
%                 M = medfilt2(M,'symmetric');

                CC = bwconncomp(M,nbconncomp);
                statsPosClass = regionprops(CC, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity');
                nbFoundObjects = length(statsPosClass);
                if ~isempty(statsPosClass)
                    % Vector = major, minor, ecc, solidity
                    featureVector = reshape(struct2array(statsPosClass),4,nbFoundObjects)';
                    if nbShapeFeatures == 3
                        featuresPosClass(mp:mp+nbFoundObjects-1,:) = [featureVector(:,1)./featureVector(:,2), featureVector(:,3:4)];
                    elseif nbShapeFeatures == 1
                        featuresPosClass(mp:mp+nbFoundObjects-1,:) = [featureVector(:,3)];
                    end
                    mp = mp + nbFoundObjects;
                end
                % Extract features for the negative class
                % currently the only way to do so is by using the stuff detected as
                % being of class OOI (as determined by a thresholding on d1), but isn't
                % (as determined by clusterObjOfInterest)
                M = reshape((d1 > minSignificanceProb).*(~clusterObjOfInterest),a(1),a(2));
                CC = bwconncomp(M,nbconncomp);
                statsNegClass = regionprops(CC, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity');
                nbFoundObjects = length(statsNegClass);
                if ~isempty(statsNegClass)
                    % Vector = major, minor, ecc, solidity
                    featureVector = reshape(struct2array(statsNegClass),4,nbFoundObjects)';
                    if nbShapeFeatures == 3
                        featuresNegClass(mn:mn+nbFoundObjects-1,:) = [featureVector(:,1)./featureVector(:,2), featureVector(:,3:4)];
                    elseif nbShapeFeatures == 1
                        featuresNegClass(mn:mn+nbFoundObjects-1,:) = [featureVector(:,3)];
                    end
                    
                    mn = mn + nbFoundObjects;
                end
            end
            % Now train the SVM
            disp('Training SVM')
            datestr(now)
            SVMModel = fitcsvm([featuresNegClass; featuresPosClass],[-ones(size(featuresNegClass,1),1); ones(size(featuresPosClass,1),1)],...
		'ClassNames', [-1 1],...
                'KernelFunction','rbf','Standardize',true, ...
                'PredictorNames', knobs.featuresList);
            SVMModel = fitSVMPosterior(SVMModel);
            datestr(now)
            matname = ['trained','I',num2str(nbimages), '_C',num2str(nbcolors),'_PC',num2str(nbcomponentsPOI),'_NPC',num2str(nbcomponentsNonPOI),'_NF',num2str(nbShapeFeatures),'_NCC',num2str(nbconncomp),'.mat'];
            save(matname, 'poiGM', 'nonpoiGM', 'SVMModel', 'knobs');
            
        end
    end
end
1;
