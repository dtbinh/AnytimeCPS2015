function clusterObjOfInterest = cluster_with_gmm(d1,d2,minAcceptanceProb,minSignificanceProb,minAcceptanceProbScalingFactor)

% clusterObjOfInterest = d1 > d2;

clusterObjOfInterest = 0; %initialize while
while (nnz(clusterObjOfInterest)==0 && minAcceptanceProb >= minSignificanceProb)
    minAcceptanceProb = minAcceptanceProb*minAcceptanceProbScalingFactor;
    clusterObjOfInterest = (d1 > max(d2,minAcceptanceProb));
end
% minAcceptanceProb