function [A, B1, B2] = discmodel(Ac, Bc, T, delta)
% Discretize the continuous plant model (Ac, Bc)
%   [A, B1, B2] = discmodel(Ac, Bc, T, delta)
% Returns system matrices (A, B1, B2) of the discrete model with sampling
% time T > 0 and delay time 0 <= delta <= T. The discrete dynamics is:
%   x((k+1)T) = A*x(kT) + B1*u(k-1) + B2*u(k)
%
% See also: C2D
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

assert(T > 0, 'Sampling time T must be positive.');
assert(0 <= delta && delta <= T, 'Time delay delta must be in [0, T].');

% A matrix using expm
A = expm(Ac*T);


%% Compute B1 and B2
% $B_1 = \int_{0}^{\delta} e^{A_c (T-t)} B_c dt$
% We can compute as $B_1 = e^{A_c (T-\delta)} \int_{0}^{\delta} e^{A_c
% (\delta-t)} B_c dt$ where the integral can be calculated by C2D.
% Similarly, $B_2 = \int_{0}^{T-\delta} e^{A_c ((T-\delta)-t)} B_c dt$
% where the integral can be calculated by C2D.

% temp system used for c2d
[n, m] = size(Bc);
sys = ss(Ac, Bc, zeros(1, n), zeros(1, m));

[Atmp, B2] = ssdata( c2d(sys, T-delta) );  %Atmp = expm(Ac*(T-delta))
[~, B1] = ssdata( c2d(sys, delta) );
B1 = Atmp * B1;

end