function res = colfun(M, f)
% Apply function f to each column of M, and concatenate the scalar results in
% a column vector.

n = size(M, 2);
res = zeros(n, 1);
for ii = 1:n
    res(ii) = feval(f, M(:, ii));
end

end