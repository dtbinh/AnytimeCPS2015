% RMPC with Anytime Estimation
% Example: simple vehicle in 2-D space.
% Not yet finished

%% Clear the workspace
clear all

%% System setup

% Continuous dynamics
Acont=[0 0 1 0;0 0 0 1;0 0 0 0;0 0 0 0];
Bcont=[0 0;0 0;1 0;0 1];

nx = size(Acont, 1);
nu = size(Bcont, 2);

T = 0.02;  % Sampling time

% Norm types of noise & accuracy bounds
% Currently only inf and 1 are supported
pw = inf;
pe = inf;

wmax = 0;  % system noise bound
assert(wmax >= 0, 'wmax must be non-negative.');
WSet = polyNormSet(nx, pw, wmax);


% Estimation modes: pairs of (delta, epsilon)
delta0 = 0.004; epsilon0 = 0.1;
modes = {[delta0 epsilon0], [delta0/2 epsilon0*sqrt(2)], [delta0/4 epsilon0*2]};
nModes = length(modes);

wmax = 0;

% The state and control input constraints
theta = pi/180*45;
Pos_set = [cos(theta) -sin(theta); sin(theta) cos(theta)] * ...
    Polyhedron([-20 0;0 15;60 15;70 0;60 -15;0 -15]); % Rotate set by theta ccw

Vel_set = Polyhedron('lb', -20*ones(2, 1), 'ub', 20*ones(2,1));

Xset = Pos_set * Vel_set;
Xset.minHRep();

SS = struct('H', Xset.A, 'K', Xset.b);
UU = struct('H', [eye(nu); -eye(nu)], 'K', 4*ones(nu*2, 1));


% RMPC parameters
N = 20;  % horizon length
stagecost = @(x,u) x'*x;  % Stage cost function
estimcost = @(m) modes{m}(1);  % Estimation cost function, m is mode index
alpha = 0;  % weight for estimation cost


%% Dynamics & precomputed values for each mode

sys = repmat(struct('A', [], 'B1', [], 'B2', [], 'Ahat', [], 'Bhat', []), nModes, 1);
RMPC = repmat(struct(...
    'K', [], 'Ctrl', [], 'maxepsk', 0 ...
    ), nModes, 1);

for ii = 1:nModes
    fprintf('Offline computation for mode %d.\n', ii);
    
    delta = modes{ii}(1);
    epsilon = modes{ii}(2);
    
    % The dynamics of the mode
    [sys(ii).A, sys(ii).B1, sys(ii).B2] = discmodel(Acont, Bcont, T, delta);
    Ahat = [sys(ii).A, sys(ii).B1; zeros(nu, nx+nu)];
    Bhat = [sys(ii).B2; eye(nu)];
    sys(ii).Ahat = Ahat;
    sys(ii).Bhat = Bhat;
    
    % The nominal feedback control
    K = -dlqr(Ahat, Bhat, blkdiag(1*eye(nx), 1e2*eye(nu)), 1e-6*eye(nu));
    RMPC(ii).K = K;
    
    % The sequence of constraint sets
    Zs = calcSetsFixed( sys(ii), SS, UU, N, K, pw, pe );
    
    % The final constraint set for computing terminal set
    ZN = Zs(end);
    ZN.K = ZN.K*[1; wmax; epsilon; epsilon];
    
    % Check if ZN is empty
    if isEmptySet(Polyhedron(ZN.H, ZN.K))
        error('Terminal set for mode %d is empty. Please change the design.', ii);
    end

    % The \hat{W} set = {w + A*e - e}
    ESet = polyNormSet(nx, pe, epsilon);
    What = WSet + sys(ii).A*ESet + (-ESet);
    What.minHRep();
    Whats = struct('H', What.A, 'K', What.b);

    % The final transition matrix
    Phi = Ahat + Bhat*K;
    LN = Phi^N;

    % Compute the invariant set for computing the terminal set
    MAXITER = 5;
    fprintf('Computing invariant set...\n');
    [Cinv, status] = calcInvSet(sys(ii), UU, ZN, LN, Whats, MAXITER, []);
    assert(status == 1, 'Failed to compute invariant set for mode %d.', ii);

    PCinv = Polyhedron(Cinv.H, Cinv.K);
    PCinv.minHRep();
    Cinv = struct('H', PCinv.A, 'K', PCinv.b);
    
    % Now pre-compute the controller & feasibility check
    [RMPC(ii).Ctrl, Feas] = RMPCController(stagecost,...
        epsilon, sys(ii), N, Zs, Cinv, LN, pw, pe, 'gurobi' );
    
    [RMPC(ii).maxepsk, errorcode] = Feas{wmax};
    if errorcode
        warning('Failed to compute max epsilon_k for mode %d: %s.',...
            ii, yalmiperror(errorcode));
        RMPC(ii).maxepsk = inf;
    end
    if RMPC(ii).maxepsk < 0
        error('Mode %d is always infeasible with any epsilon_k.', ii);
        % TO FIX: reduce error epsilon, redesign K, etc.
    end
end


%% Simulation
x0 = [30; 30; 0; 0];
u0 = [0; 0];
z0 = [x0; u0];
[sysk.A, sysk.B1, sysk.B2] = discmodel(Acont, Bcont, 0.02, 0.005);
epsilon_k = epsilon / sqrt(2);

Az0 = [sysk.A, sysk.B1; zeros(2, 6)]*z0;
Bk = [sysk.B2; eye(2,2)];

tic
uk = Ctrl{{z0, Az0, Bk, epsilon_k, wmax}};
toc