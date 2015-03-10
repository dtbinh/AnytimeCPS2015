folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
GMs = load('GMs.mat');

colors      = [1,2,3];
poiGM       = GMs.poiGM;
nonpoiGM    = GMs.nonpoiGM;
minAcceptanceProbScalingFactor 	= GMs.minAcceptanceProbScalingFactor;
minSignificanceProb             = GMs.minSignificanceProb;
minAcceptanceProb               = GMs.minAcceptanceProb;
SVMModel                        = GMs.SVMModel;
muPOI                           = poiGM.mu;
SigmaPOI                        = poiGM.Sigma;
ComponentProportionPOI          = poiGM.ComponentProportion;
muNON = nonpoiGM.mu;
SigmaNON = nonpoiGM.Sigma;
ComponentProportionNON = nonpoiGM.ComponentProportion;

Alpha               = SVMModel.Alpha;
SupportVectorLabels = SVMModel.SupportVectorLabels;
KernelScale         = SVMModel.KernelParameters.Scale;
SupportVectors      = SVMModel.SupportVectors;
Bias                = SVMModel.Bias;

nbimages = 1;
for m=1:nbimages
    imageName = [folder, '/',images(m).name];
    Im=imread(imageName);
    run_perception_module_for_srcgen(Im, colors, minAcceptanceProbScalingFactor, minSignificanceProb, minAcceptanceProb, ...
        muPOI, SigmaPOI, ComponentProportionPOI, ...
        muNON, SigmaNON, ComponentProportionNON, ...
        Alpha, SupportVectorLabels, KernelScale, SupportVectors, Bias);
end

