function J = preprocess_img(I)
assert(size(I,3)==3);
I = double(I);
% Remove the NaNs to avoid weirdness when computing probabilities 
S = isnan(I);
I = S.*zeros(size(I)) + (~S).*I;
% Normalize
s = sum(I,3);
S = repmat((s == 0),1,1,3);
s(s==0) = 1;
J = S.*I + (~S).*(I./repmat(s,1,1,3));
if any(any(any(isnan(J),3),2))
    error('Still have NaNs in the normalized image - this should not happen.')
end