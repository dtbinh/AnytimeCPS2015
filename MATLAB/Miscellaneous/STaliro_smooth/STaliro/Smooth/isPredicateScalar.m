function isScalar = isPredicateScalar(SmoothOpt)

% output: vector of length = num of preds, if 1 then scalar, 0 not
isScalar = zeros(numel(SmoothOpt.preds.Sets),1);
for i =1:numel(SmoothOpt.preds.Sets)
    A = SmoothOpt.preds.Sets(i).A;
    isScalar(i) = (sum(sum(A~=0)>0)==1);
    
end

