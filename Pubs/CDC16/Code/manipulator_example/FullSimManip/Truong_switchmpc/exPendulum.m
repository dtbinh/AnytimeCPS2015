% RMPC with Anytime Estimation
% Example: inverted pendulums on carts.

%% Clear the workspace
clear all
yalmip('clear')

%% System setup

% Continuous dynamics
[Acont1, Bcont1, C1] = pendulum_on_cart_model;

% Two carts
Acont = blkdiag(Acont1, Acont1);
Bcont = blkdiag(Bcont1, Bcont1);
C = blkdiag(C1, C1);

% scale is the state scaling factors so that we can use a common norm
% radius for all state variables. Let x be the actual state variables
% (where x consists of the position, velocity, angle, angular velocity) and
% x1 = scale.*x, then |x1| <= epsilon.  For example, if |pos|
% <= 0.1 but |angle| <= 0.01, and we use common norm radius 0.1, then
% stateScale(3) = 10 because we have to scale 'angle' by 10 times to scale
% its actual range to [-0.1, 0.1].

stateScale = repmat([1; 1; 3; 3], 2, 1);
if isempty(stateScale)
    SCALE = 1;
else
    % We scale the plant's dynamics, so the RMPC does not change; but we
    % need to take the scaling factors into account in the simulation
    % (conversion between actual states and transformed/scaled states.
    SCALE = stateScale(:);
    [Acont, Bcont, C] = scaleLTI(Acont, Bcont, C, SCALE);
end

nx = size(Acont, 1);
nu = size(Bcont, 2);

T = 0.025;  % Sampling time

% Norm types of noise & accuracy bounds
% Currently only inf and 1 are supported
pw = inf;
pe = inf;

wmax = 0;  % system noise bound
assert(wmax >= 0, 'wmax must be non-negative.');


% Estimation modes: pairs of (delta, epsilon)
delta0 = 0.002; epsilon0 = 0.01;  % the worst accuracy

modes = struct('delta', {delta0, delta0*2, delta0*4},...
    'epsilon', {epsilon0, epsilon0/sqrt(2), epsilon0/2});

nModes = length(modes);


% The state and control input constraints
%Xset = Polyhedron('lb', repmat([-5; -4; -0.2; -2], 2, 1), 'ub', repmat([7; 4; 0.2; 2], 2, 1));
%Xset = Polyhedron('lb', repmat([-10; -10; -0.2; -10], 2, 1), 'ub', repmat([20; 10; 0.2; 10], 2, 1)); 
Xset = Polyhedron('lb', repmat([-4; -inf; -0.2; -inf], 2, 1), 'ub', repmat([6; inf; 0.2; inf], 2, 1));
Xset = Polyhedron([Xset.A; 1 0 0 0 -1 0 0 0], [Xset.b; -1]);  % constraint 2 carts to be at least some distance apart
Xset.minHRep;

% Because the state variables may be scaled, we need to scale the Xset too
% as the plant's dynamics are scaled.
if ~isempty(stateScale)
    Xset = diag(SCALE)*Xset;
end
Xset.minHRep;

SS = struct('H', Xset.A, 'K', Xset.b);

Uset = Polyhedron('lb', [-10; -10], 'ub', [10; 10]);
UU = struct('H', Uset.A, 'K', Uset.b);


% RMPC parameters
N = 25;  % horizon length: >= 0.5s should be fine; the longer the better

% Stage cost function
% x = stateScale.*[pos; vel; angle; angle_vel]. To drive pos and angle to an
% equilibrium (velocities will inherently be 0 to keep pos and angle at the
% equilibrium), we need to incur more cost on these two variables.
stagecost = @(x,u) x(1)^2 + 1*x(3)^2 + 1e-2*x(2)^2 + 1e-2*x(4)^2 + ...  % first cart goes to 0
    (x(5)-2)^2 + 1*x(7)^2 + 1e-2*x(6)^2 + 1e-2*x(8)^2;   % second cart goes to other position

finalcost = @(x) 0;


%% Dynamics & precomputed values for each mode

sys = repmat(struct('A', [], 'B1', [], 'B2', [], 'Ahat', [], 'Bhat', []), nModes, 1);
RMPC = repmat(struct(...
    'K', [], 'Ctrl', [], 'maxepsk', inf,...
    'Zs', [], 'Cinv', [], 'LNF', []),...
    nModes, 1);

for ii = 1:nModes
    fprintf('Offline computation for mode %d.\n', ii);
    
    delta = modes(ii).delta;
    epsilon = modes(ii).epsilon;
    
    % The dynamics of the mode
    [sys(ii).A, sys(ii).B1, sys(ii).B2] = discmodel(Acont, Bcont, T, delta);
    Ahat = [sys(ii).A, sys(ii).B1; zeros(nu, nx+nu)];
    Bhat = [sys(ii).B2; eye(nu)];
    sys(ii).Ahat = Ahat;
    sys(ii).Bhat = Bhat;
    
    % The nominal feedback control
    % We can change the weight for state vs. control in the cost function
    % to adjust the nominal control K.
    LQR_Q = blkdiag(1, 1, 100, 1, 1, 1, 100, 1, 1e-2*eye(nu));
    LQR_R = 1e-8*eye(nu);
    
    % Fixed (time-invariant) K
    %K = -dlqr(Ahat, Bhat, LQR_Q, LQR_R);
    
    % Time-varying K (computed by finite-horizon LQR)
    K = dlqrft(Ahat, Bhat, N, LQR_Q, LQR_R, LQR_Q);

    RMPC(ii).K = K;
    
    % The sequence of constraint sets
    [Zs, LNF] = calcSets( sys(ii), SS, UU, N, K, pw, pe );
    

    % The final constraint set for computing terminal set
    ZN = Zs(end);
    ZN.K = ZN.K*[1; wmax; epsilon; epsilon];
    
    % Check if ZN is empty
    if isEmptySet(Polyhedron(ZN.H, ZN.K))
        error('Terminal set for mode %d is empty. Please change the design.', ii);
    end


    % Compute the invariant set for computing the terminal set
    MAXITER = 2;
    fprintf('Computing invariant set...\n');
    [Cinv, status] = calcInvSet(sys(ii), ZN, LNF, wmax, epsilon, pw, pe, MAXITER, 1);
    if status == 0
        disp('Hooray!!! Successfully computed invariant set.');
    elseif status == 1
        fprintf('Computing invariant set for mode %d reached max iteration. Use the last set (not invariant set).\n', ii);
    else
        error('Critically failed to compute invariant set for mode %d.\n', ii);
    end
    
    PCinv = Polyhedron(Cinv.H, Cinv.K);
    assert(~isEmptySet(PCinv), 'Invariant set for mode %d is empty. Failed!', ii);

    PCinv.minHRep();
    Cinv = struct('H', PCinv.A, 'K', PCinv.b);
    
    RMPC(ii).Zs = Zs;
    RMPC(ii).Cinv = Cinv;
    RMPC(ii).LNF = LNF;
    
    % Now pre-compute the controller (& feasibility check NOT FOR NOW)
    [RMPC(ii).Ctrl, Feas] = RMPCController(stagecost, finalcost,...
        epsilon, sys(ii), N, RMPC(ii).Zs, RMPC(ii).Cinv, RMPC(ii).LNF, pw, pe, 'gurobi' );
    
    RMPC(ii).maxepsk = inf;
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


%% Prepare Simulation

estimcost = [modes.delta];  % Estimation cost function, m is mode index
alpha = 20;  % weight for estimation cost

% Initial state, control, and mode
x0 = SCALE.*[-2; 0; -0.05; 0; 3; 0; 0.05; 0];
u0 = [0; 0];
mode0 = 1;

assert(Xset.contains(x0), 'x0 is not valid.');
assert(Uset.contains(u0), 'u0 is not valid.');
assert(1 <= mode0 && mode0 <= nModes, 'Initial mode mode0 is not valid.');

z0 = [x0; u0];

nSimSteps = 600;  % number of simulation steps

% Initialize history variables
Xout = zeros(nx, nSimSteps);
XEout = zeros(nx, nSimSteps-1);  % estimated state
Yout = zeros(size(C, 1), nSimSteps);
Uout = zeros(nu, nSimSteps); % Uout(1) is u_{-1}, Uout(2) is u_0, etc.
Mout = zeros(1, nSimSteps);  % modes
CostOut = zeros(1, nSimSteps-1);  % RMPC cost

Xout(:, 1) = x0;
Uout(:, 1) = u0;
Mout(1) = mode0;
Yout(:, 1) = C*x0;

%% Simulation
xtrue = x0;
curMode = mode0;
u_prev = u0;

disp('Start simulation...');

for iStep = 2:nSimSteps
    fprintf('Time step %d ...\n', iStep-2);
    
    % Obtain the state estimate
    epsilon_k = modes(curMode).epsilon;
    
    % If x_k is obtained from other means, e.g. vision algorithm, then
    % remember to scale it by SCALE
    x_k = xtrue + randStateError(nx, pe, epsilon_k);
    z0 = [x_k; u_prev];
    
    Az0 = sys(curMode).Ahat*z0;
    Bhat = sys(curMode).Bhat;
    
    % Compute control and cost for each valid mode
    cost = inf;
    u_k = [];
    nextMode = 0;
    
    for ii = 1:nModes
        if RMPC(ii).maxepsk >= epsilon_k
            [sol, errorcode] = RMPC(ii).Ctrl{{z0, Az0, Bhat, epsilon_k, wmax}};
%             [ruk, robj, errorcode, diag] = RMPCControl( stagecost, finalcost,...
%                 modes(ii).epsilon, sys(ii), N, RMPC(ii).Zs, RMPC(ii).Cinv, RMPC(ii).LNF, pw, pe,...
%                 z0, Az0, Bhat, epsilon_k, wmax);
%             sol = {ruk, robj};
            if errorcode ~= 0
                warning('Failed to solve RMPC for mode %d at time step %d: %s.\n',...
                    ii, iStep-2, yalmiperror(errorcode));
            else
                modeCost = sol{2} + alpha * estimcost(ii);
                if modeCost < cost
                    cost = modeCost;
                    u_k = sol{1};
                    nextMode = ii;
                end
            end
        else
            fprintf('Not solve RMPC for mode %d at time step %d due to large initial epsilon: %g > %g.\n',...
                ii, iStep-2, epsilon_k, RMPC(ii).maxepsk);
        end
    end

    if nextMode == 0
        error('Failed to compute control u_k for all modes at time step %d.', iStep-2);
    end
    
    % Update true state
    xtrue = sys(curMode).A*xtrue + ...
        sys(curMode).B1*u_prev + sys(curMode).B2*u_k + ...
        randStateError(nx, pw, wmax);
    
    % Save the trajectories
    Xout(:, iStep) = xtrue;
    Yout(:, iStep) = C*xtrue;
    XEout(:, iStep-1) = x_k;
    Uout(:, iStep) = u_k;
    Mout(iStep) = nextMode;
    CostOut(iStep-1) = cost;
    
    % update current variables
    curMode = nextMode;
    u_prev = u_k;
end


%% Plotting
YEout = C*XEout;

figure;
subplot(2,1,1);
plot(Yout([1,3],:)'); title('Position');
hold on
plot(YEout([1,3],:)', 'r')

subplot(2,1,2);
plot(Yout([2,4],:)'); title('Angle');
hold on
plot(YEout([2,4],:)', 'r')


figure;
subplot(2,1,1);
stairs(Uout'); title('Control');
subplot(2,1,2);
stairs(Mout); title('Mode');
ylim([0.9 (nModes+0.1)]);


figure;
stairs(CostOut); title('Cost');
