function Zs = calcSetsFixed_old( sys, SS, UU, N, K, pw, pe )
%CALCSETSFIXED Compute all constraint sets for Anytime RMPC with fixed K.
%   Zs = calcSetsFixed( sys, SS, UU, K, pw, pe )
%Inputs:
%   sys.A, sys.B1, sys.B2 specify the discrete dynamics.
%   SS.H, SS.K specify the state constraint {x : SS.H*x <= SS.K}
%   UU.H, UU.K specify the input constraint {u : UU.H*u <= UU.K}; if UU=[]
%               then input is unconstrained.
%   N is the horizon (>= 1).
%   K is the constant (time-invariant) nominal state feedback matrix
%   pw is the norm for disturbances w (pw = 1, 2, inf)
%   pe is the norm for estimation error e (pe = 1, 2, inf)
%
%Output:
%   Zs is a structure array specifying all the Zj sets, for j = 0..N
%   Zs(j+1) is Zj and has these fields: .H, .K where
%       Zj = {z | H*z <= K*[1; w; epsilon; epsilon_k]}
%   in which w is the bound on disturbances, and .K must have 4 columns.
%
%Note that parameter checking is minimal, so you should make sure that the
%function is called with valid parameters.
%
%See also: DISCMODEL
%
% (C) 2014 by Truong X. Nghiem

%%%%%%%%%%%%%%%%%%%%%
% This code uses the tighter constraint sets for RMPC, but it seems not
% working correctly (the theory of the constraint sets, not the code).
%%%%%%%%%%%%%%%%%%%%%

%% Process the parameters
assert(N >= 1, 'MPC horizon N must be at least 1.');

qw = supportFunNorm(pw);
qe = supportFunNorm(pe);

[nx, nu] = size(sys.B1);

if isempty(UU)
    UU = struct('H', zeros(0, nu), 'K', zeros(0, 1));
end

%% Construct required matrices

Ahat =  [sys.A, sys.B1; zeros(nu, nx+nu)];
Fhat = [eye(nx); zeros(nu, nx)];
Bhat = [sys.B2; eye(nu)]; 
Phi = Ahat + Bhat*K;
Kx = K(:, 1:nx);

Hz = blkdiag(SS.H, UU.H);
Zs = repmat(...
    struct('H', Hz, 'K', [SS.K, zeros(length(SS.K), 3); UU.K, zeros(length(UU.K), 3)]),...
    N+1, 1);
Hz = Hz.';

%% Compute the sets using support functions

% Z0 is special
Zs(1).K(:, 4) = -colfun(Hz, @(eta) norm(eta(1:nx), qe));

% Z1
PhiF = Fhat;
Zs(2).K(:, 2) = -colfun(Hz, @(eta) norm(PhiF.'*eta, qw));
Zs(2).K(:, 4) = -colfun(Hz, @(eta) norm((PhiF*sys.A).'*eta, qe));

% Zj for j >= 2
if N < 2, return; end

PhiBK = -Bhat*Kx;
for jj = 2:N
    PhiF = Phi*PhiF;  % update Phi^{j-1}*Fhat
    Zs(jj+1).K(:, 2) = Zs(jj).K(:, 2) ...
        - colfun(Hz, @(eta) norm(PhiF.'*eta, qw));
    
    Zs(jj+1).K(:, 3) = Zs(jj).K(:, 3) ...
        - colfun(Hz, @(eta) norm(PhiBK.'*eta, qe));
    PhiBK = Phi*PhiBK; % update to next -Phi^{j-2}*Bhat*Kx
    
    Zs(jj+1).K(:, 4) = -colfun(Hz, @(eta) norm((PhiF*sys.A).'*eta, qe));
end

end

function q = supportFunNorm(p)
    if p == 1
        q = inf;
    elseif p == 2
        q = 2;
    elseif isinf(p)
        q = 1;
    else
        error('Check the norms: they must be 1, 2, or inf.');
    end
end
