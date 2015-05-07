function S = polyNormSet( N, P, RAD )
%POLYNORMSET Create MPT/Polyhedron set from a norm ball.
%   S = polyNormSet( N, P, RAD )
%   N: dimensions.
%   P: the norm, either 1 or inf.
%   RAD: radius in P-norm.
%
%   S is a Polyhedron in MPT version 3+
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

assert(isinf(P) || P == 1, 'Norm P must be either inf or 1.');
assert(RAD >= 0, 'Radius RAD must be non-negative.');

if RAD > 0
    if isinf(P)
        S = Polyhedron('lb', -RAD*ones(N,1), 'ub', RAD*ones(N,1));
    elseif P == 1
        S = Polyhedron([RAD*eye(N); -RAD*eye(N)]);
    end
else
    S = Polyhedron(zeros(1, N));
end

end

