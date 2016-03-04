function [ Ctrl, Feas ] = RMPCController( fobj, fobjfinal, epsilon, sys, N, Zs, Cinv, LNF, pw, pe, solver )
%RMPCCONTROLLER RMPC controller for a fixed mode using Yalmip/Optimizer.
%   [ Ctrl, Feas ] = RMPCController(fobj, epsilon, sys, N, Zs, Cinv, LN, pw, pe )
%
%Inputs:
%   fobj is a function handle of the stage cost; it must work with Yalmip's
%         sdp variables; cost_i = fobj(x_i, u_i) where x_i, u_i are sdp's.
%   epsilon > 0 is the estimation error for the fixed mode.
%   sys.A, sys.B1, sys.B2 specify the discrete dynamics.
%   N >= 0 is the MPC horizon.
%   Zs is the sequence of sets as returned by calcSetsFixed.
%   Cinv is the invariant set as returned by calcInvSet.
%   LNF is the matrix L_N*Fhat (see paper).
%   pw is the norm for disturbances w (pw = 1, 2, inf)
%   pe is the norm for estimation error e (pe = 1, 2, inf)
%   solver is a string which specifies the solver used to solve the
%         problem. This argument is required for Yalmip's optimizer to
%         work. The constraints are linear, hence the type of solver
%         depends on the cost function (e.g. LP, QP,...).
%
%Outputs:
%   Ctrl: an Yalmip/Optimizer object to compute the next control u_k
%           sol = Ctrl{{z0, Az0, B, ek, w}}
%         where z0 = [xhat_k; u_{k-1}], Az0 = Ahat(delta_k)*z0, B =
%         Bhat(delta_k), ek = epsilon_k, w = bound of disturbances,
%         Note that we use Az0 instead of A because of the way these
%         parameters enter the optimization. The output sol is a cell array
%         of {uk, cost}.
%
%   Feas: an Yalmip/Optimizer object to compute the upperbound on epsilon_k
%         necessary for the RMPC optimization to be feasible (but not
%         sufficient).
%           ek_max = Feas{w}
%
%
%Require: Yalmip with support for general optimizer command.
%
%See also: CALCSETSFIXED, CALCINVSET
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

assert(N >= 0, 'RMPC horizon N must be non-negative.');
assert(length(Zs) == 1+N, 'Zs must contain N+1 sets.');
assert(isa(fobj, 'function_handle'), 'fobj must be a function handle.');

%% Compute necessary values
[nx, nu] = size(sys.B1);
Ahat =  [sys.A, sys.B1; zeros(nu, nx+nu)];
Bhat = [sys.B2; eye(nu)];

qw = supportFunNorm(pw);
qe = supportFunNorm(pe);


%% Define the sdp variables
sz0 = sdpvar(nx+nu, 1);
sAz0 = sdpvar(nx+nu, 1);
sB = sdpvar(nx+nu, nu);
sEps_k = sdpvar(1);
sW = sdpvar(1);

sU = sdpvar(nu*ones(1,N+1),ones(1,N+1));

%% Construct the RMPC constraints and cost function

% The dynamics at jj = 0 is special, so we initialize the constraints and
% cost to the case with jj = 0.
z = sz0;
constraints = Zs(1).H*z <= Zs(1).K*[1; sW; epsilon; sEps_k];
cost = fobj(z(1:nx,1), sU{1});

% z_1
z = sAz0 + sB*sU{1};

for jj = 2:N+1
    constraints = [constraints,...
        Zs(jj).H*z <= Zs(jj).K*[1; sW; epsilon; sEps_k]]; %#ok<AGROW>
    cost = cost + fobj(z(1:nx,1), sU{jj});

    % update z according to the dynamics of fixed mode
    z = Ahat*z + Bhat*sU{jj};
end

% Final cost
cost = cost + fobjfinal(z(1:nx,1));

% The terminal constraint
if all(all(abs(LNF) < eps))
    % if LNF ~ 0 then we don't need to consider the disturbances What
    constraints = [constraints, Cinv.H*z <= Cinv.K];
else
    HT = Cinv.H.';
    constraints = [constraints,...
        Cinv.H*z <= Cinv.K - epsilon*colfun(HT, @(eta) norm(-LNF.'*eta, qe)) ...
                    - sW*colfun(HT, @(eta) norm(LNF.'*eta, qw)) ...
                    - sEps_k*colfun(HT, @(eta) norm((LNF*sys.A).'*eta, qe))];
end


%% Create the Yalmip/Optimizer for RMPC controller
Ctrl = optimizer(constraints, cost, sdpsettings('solver', ['+' solver]),...
    {sz0, sAz0, sB, sEps_k, sW}, {sU{1}, cost});


%% Create the feasibility optimizer if desired
if nargout < 2, return; end

z = sdpvar(nx+nu, 1);  % dummy variable to ensure constraint sets are non-empty

constraints = Zs(1).H*z <= Zs(1).K*[1; sW; epsilon; sEps_k];
for jj = 2:N+1
    constraints = [constraints,...
        Zs(jj).H*z <= Zs(jj).K*[1; sW; epsilon; sEps_k]]; %#ok<AGROW>
end
% The terminal constraint
if all(all(abs(LNF) < eps))
    % if LNF ~ 0 then we don't need to consider the disturbances What
    constraints = [constraints, Cinv.H*z <= Cinv.K];
else
    constraints = [constraints,...
        Cinv.H*z <= Cinv.K - epsilon*colfun(HT, @(eta) norm(-LNF.'*eta, qe)) ...
                    - sW*colfun(HT, @(eta) norm(LNF.'*eta, qw)) ...
                    - sEps_k*colfun(HT, @(eta) norm((LNF*sys.A).'*eta, qe))];
end

Feas = optimizer(constraints, -sEps_k, [], sW, sEps_k);

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