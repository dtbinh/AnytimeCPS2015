% all generated classifiers are copied to the directory 'classifiers'
% classifiers are trained using haar features
% parameters are read from 'params_train.txt'
% all negative images are in a folder called 'negativeFolder'

load posMat.mat

% read from 14th line (row 1), coz the first 13 lines are description
params = dlmread('params_train.txt','\t',16,0);

% create a parallel pool
% fprintf('creating Parallel Pool\n');
% parpool;
% fprintf('Parallel pool created\n');

% create results folder if it doesnt exists
if exist('classifiers','dir') == 0
    mkdir('classifiers')
end

% loop over the parameter list
for i = 1:size(params,1)
    fprintf('Training classifier %d\n',i);
    % ObjectTrainingSize
    if params(i,1)*params(i,2) == 0 || params(i,1) < 4 || params(i,2) < 4  
        ots = 'Auto';
    else
        ots = [params(i,1), params(i,2)];
    end
    
    % NegativeSamplesFactor
    if params(i,3) == 0
        nsf = 2;
    else
        nsf = params(i,3);
    end
    
    % NumCascadedStages
    if params(i,4) == 0
        ncs = 20;
    else
        ncs = params(i,4);
    end
    
    % FalseAlarmRate
    if params(i,5) == 0 || params(i,5) > 1
        far = 0.5;
    else
        far = params(i,5);
    end
    
    % TruePositiveRate
    if params(i,6) == 0 || params(i,6) > 1
        tpr = 0.995;
    else
        tpr = params(i,6);
    end
    
    nsf
    ncs
    far
    tpr
    
    % generate name of classifier file
    name = strcat('cascade_',num2str(params(i,1)),'_',num2str(params(i,2)),'_',...
        num2str(params(i,3)),'_',num2str(params(i,4)),'_',...
        num2str(params(i,5)),'_',num2str(params(i,6)),'.xml');
    
    trainCascadeObjectDetector(name, positiveInstances, 'negativeFolder', ...
        'ObjectTrainingSize', 'Auto', 'NegativeSamplesFactor', nsf, ...
        'NumCascadeStages', ncs,  'FalseAlarmRate', far, ...
        'TruePositiveRate', tpr, 'FeatureType', 'Haar');
    
    fprintf('Classifier for parameters[%d] created and saved\n',i);
end

movefile('*.xml','classifiers/');
%%
% 
% tic;
% parfor i = 1:1000000
%     f = 1;
%     if mod(i,10) == 0
%         fprintf('i is %d\n',f+i);
%         
%     end
%     fprintf('hello %d\n',i);
% end
% toc;
