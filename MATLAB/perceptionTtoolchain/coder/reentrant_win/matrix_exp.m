function Y = matrix_exp(X) %#codegen
    %
    % The function matrix_exp computes matrix exponential of 
    % the input matrix using Taylor series and returns the 
    % computed output.
    E = zeros(size(X));
    F = eye(size(X));
    k = 1;
    while norm(E+F-E,1) > 0
        E = E + F;
        F = X*F/k;
        k = k+1;
    end
    Y = E;
    
