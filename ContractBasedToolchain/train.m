function [] = train(folderPath)
addpath(genpath(folderPath))
fprintf('Changing Directory to %s\n',folderPath);
cd(folderPath);
fprintf('Generating Positive Instances for Cascade Object Detector\n');
genPosInstances;
genClassifiers;
end