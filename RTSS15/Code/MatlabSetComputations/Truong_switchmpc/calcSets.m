function [Zs, LNF] = calcSets( sys, SS, UU, N, Ks, pw, pe )
%CALCSETSFIXED Compute all constraint sets for Anytime RMPC with varying K.
%   [Zs, LNF] = calcSetsFixed( sys, SS, UU, Ks, pw, pe )
%Inputs:
%   sys.A, sys.B1, sys.B2 specify the discrete dynamics.
%   SS.H, SS.K specify the state constraint {x : SS.H*x <= SS.K}
%   UU.H, UU.K specify the input constraint {u : UU.H*u <= UU.K}; if UU=[]
%               then input is unconstrained.
%   N is the horizon (>= 1).
%   Ks is the sequence of nominal state feedback matrices. It may be a cell
%       array of N matrices, or a single matrix (in that case, Ks is
%       time-invariant).
%   pw is the norm for disturbances w (pw = 1, 2, inf)
%   pe is the norm for estimation error e (pe = 1, 2, inf)
%
%Output:
%   Zs is a structure array specifying all the Zj sets, for j = 0..N
%   Zs(j+1) is Zj and has these fields: .H, .K where
%       Zj = {z | H*z <= K*[1; w; epsilon; epsilon_k]}
%      in which w is the bound on disturbances, and .K must have 4 columns.
%   LNF is the matrix L_N*Fhat (used to compute invariant/terminal set).
%
%Note that parameter checking is minimal, so you should make sure that the
%function is called with valid parameters.
%
%See also: DISCMODEL
%
% (C) 2014 by Truong X. Nghiem

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

% Check if K is varying or time-invariant, and precompute Phi if possible
isKFixed = ~iscell(Ks);
if isKFixed
    PhiFixed = Ahat + Bhat*Ks;
else
    assert(length(Ks) >= N, 'Ks must have at least N matrices.');
end

Hz = blkdiag(SS.H, UU.H);
Zs = repmat(...
    struct('H', Hz, 'K', [SS.K, zeros(length(SS.K), 3); UU.K, zeros(length(UU.K), 3)]),...
    N+1, 1);
Hz = Hz.';

%% Compute the sets using support functions

% Z0 is special
Zs(1).K(:, 4) = -colfun(Hz, @(eta) norm(eta(1:nx), qe));

% Zj
% If Zj = {Hz <= K - a*w - b*epsilon - c*epsilon_k}
% then Z{j+1} = Zj(epsilon, epsilon) - Lj*Fhat*What(epsilon_k, epsilon)
%             = {Hz <= K - (a + norm((Lj*Fhat)'*H'))*w
%                        - (b + c + norm(-(Lj*Fhat)'*H'))*epsilon
%                        - norm((Lj*Fhat*A)'*H')*epsilon_k

LjF = Fhat;  % L_j*Fhat, for j = 0, 1, 2...
for jj = 1:N
    
    Zs(jj+1).K(:, 2) = Zs(jj).K(:, 2) ...
        - colfun(Hz, @(eta) norm(LjF.'*eta, qw));
    
    Zs(jj+1).K(:, 3) = Zs(jj).K(:, 3) + Zs(jj).K(:, 4) ...
        - colfun(Hz, @(eta) norm(-LjF.'*eta, qe));
    
    Zs(jj+1).K(:, 4) = -colfun(Hz, @(eta) norm((LjF*sys.A).'*eta, qe));
    
    LjF = Phi(jj-1)*LjF;  % update Lj*Fhat
end

% After the loop, LjF is L_N*Fhat
LNF = LjF;

    function Phij = Phi(j)
        % j = 0,...,N-1
        if isKFixed
            Phij = PhiFixed;
        else
            Phij = Ahat + Bhat*Ks{j+1};
        end
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
