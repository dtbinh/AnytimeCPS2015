function [signed_distance,close_pt] = getSignedDistanceFast(x,P)
%% DO NOT USE, WRONG
% compute signed distance between polytope P and point x
% Analytical formula for distance used

% input:
% P: MPT Polyhedron
% x: point to compute signed distance for
% output:
% signed_distance
% close_pt: zeros, nothing here.


dim = size(P.A,2);
numConstrs = size(P.A,1);
optvals = zeros(numConstrs,1);
close_pt = zeros(dim,1);

for i = 1:numConstrs
    optvals(i) = abs(P.b(i)-P.A(i,:)*x)/(norm(P.A(i,:)));
end
[signed_distance,~] = min(optvals);

if(~isInside(P,x))
    signed_distance = -signed_distance;
end

%% vect attempt

