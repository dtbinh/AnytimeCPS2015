function [ A, B, C ] = scaleLTI( A, B, C, stateScale )
%SCALELTI Transform an LTI system by scaling its state variables.
%   [ A1, B1, C1 ] = scaleLTI( A, B, C, stateScale )
%Transform the LTI system x' = Ax +Bu, y = Cx by change of variables:
%   x1 = diag(stateScale)*x
%The output is the new LTI: x1' = A1*x + B1*u, y = C1*x1, where y is the
%same as in the original system.
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

% Let M = diag(stateScale) then
% new state z = M*x, P = M^{-1} = diag(1./stateScale)
% z' = M*x' = M*(A*P*z + B*u) = M*A*P*z + M*B*u
% y = C*x + D*u = C*P*z + D*u

SCALE = diag(stateScale);
SCALEINV = diag(1./stateScale);
A = SCALE * A * SCALEINV;
B = SCALE * B;
C = C * SCALEINV;

end

