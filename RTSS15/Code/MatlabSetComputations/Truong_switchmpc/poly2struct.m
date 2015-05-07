function T = poly2struct(P)
% Convert a single MPT's Polyhedron object to a structure T.H, T.K such
% that P = {x | T.H*x <= T.K}.
%
% (C) 2014 by Truong X. Nghiem

assert(length(P) == 1, 'P must be a single Polyhedron, not a vector/union.');

T = struct('H', P.A, 'K', P.b);
if ~isempty(P.be)
    T.H = [T.H; P.Ae; -P.Ae];
    T.K = [T.K; P.be; -P.be];
end

end