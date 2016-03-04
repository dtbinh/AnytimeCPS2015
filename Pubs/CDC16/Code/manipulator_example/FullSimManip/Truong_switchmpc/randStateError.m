function xe = randStateError(n, pe, epsilon)
% Generate random error vector of length n such that |xe|_pe <= epsilon.
% pe must be either 1 or inf.

if epsilon <= 0
    xe = zeros(n, 1);
    return;
end

if isinf(pe)
    xe = (2*rand(n,1)-1) * epsilon;
elseif pe == 1
    % generate random sum between 0 and epsilon: the sum of absolute values
    % of xe must equal this sum
    randsum = rand * epsilon;
    if randsum == 0
        xe = zeros(n, 1);
    else
        % generate random numbers between -1 and 1, then scale them so that
        % their sum of absolute values equal randsum
        xe = (2*rand(n,1)-1);
        scale = randsum / sum(abs(xe));
        xe = xe * scale;
    end
else
    error('Only 1-norm and inf-norm are supported.');
end

end