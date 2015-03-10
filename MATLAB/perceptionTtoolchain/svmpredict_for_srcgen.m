function label = svmpredict_for_srcgen(features, Alpha, SupportVectorLabels, KernelScale, SupportVectors, Bias)

% labelAuto = predict(SVMModel, featuresPosClass);

label               = zeros(size(features,1),1);
w                   = (Alpha).*(SupportVectorLabels);
for k=1:size(features,1)
    z = features(k,:);
    s = 0;
    for i=1:length(Alpha)
        s = s + w(i)*svmRBFkernel(SupportVectors(i,:),z, KernelScale);
    end
    s = s + Bias;
    label(k) = sign(s);
    
end


end