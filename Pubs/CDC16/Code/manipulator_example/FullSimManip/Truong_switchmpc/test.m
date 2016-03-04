%%
% Acont=[0 0 1 0;0 0 0 1;0 0 0 0;0 0 0 0];
% Bcont=[0 0;0 0;1 0;0 1];
[Acont, Bcont] = pendulum_on_cart_model;

[nx, nu] = size(Bcont);

[sys.A, sys.B1, sys.B2] = discmodel(Acont, Bcont, 0.01, 0.002);
Ahat = [sys.A, sys.B1; zeros(nu, nx+nu)];
Bhat = [sys.B2; eye(nu)];
Fhat = [eye(nx); zeros(nu,nx)];
K = -dlqr(Ahat, Bhat, eye(nx+nu), 1e-6*eye(nu));

%%
% states = {'x' 'x_dot' 'phi' 'phi_dot'};
% sys_ss = ss(Acont,Bcont, eye(size(Acont)), zeros(size(Acont,1), size(Bcont,2)),'statename',states, 'outputname', states);
% 
% Kcont = lqr(sys_ss,eye(size(Acont,1)),0.1*eye(size(Bcont,2)),zeros(size(Acont,1),size(Bcont,2))); %continuous LQR design;
% closedloop = feedback(sys_ss, Kcont);
% T = linspace(0, 10, 1000);
% lsim(closedloop, zeros(1000,1), T, [2; 0; 0.05; 0]);
% Y = lsim(closedloop, zeros(1000,1), T, [2; 0; 0.05; 0]);
% U = -Kcont*Y';
% figure; plot(T, U);


%%
% Pos_set=Polyhedron([40 70;100 50;10 -10;-20 -10;-20 20]);
% vel_set=Polyhedron(5*[1 1;1 -1;-1 -1;-1 1]);
% Xset=Pos_set*vel_set;

Xset = Polyhedron('lb', [-5; -2; -0.1; -1], 'ub', [5; 2; 0.1; 1]);
SS = struct('H', Xset.A, 'K', Xset.b);

%UU = struct('H', [eye(2); -eye(2)], 'K', 150*[1; 1; 1; 1]);
Uset = Polyhedron('lb', [-10], 'ub', [10]);
UU = struct('H', Uset.A, 'K', Uset.b);

N = 100;
pw = inf;
pe = inf;
Zs = calcSetsFixed( sys, SS, UU, N, K, pw, pe );

wmax = 0;
epsilon = 0;

ZN = Zs(end);
ZN.K = ZN.K*[1; wmax; epsilon; epsilon];
if isEmptySet(Polyhedron(ZN.H, ZN.K))
    error('Z_N is empty.');
end

Phi = Ahat + Bhat*K;
LNF = Phi^N * Fhat;

%%
% profile clear
% profile on
tic;
[Cinv, status, PCinv] = calcInvSet( sys, ZN, LNF, wmax, epsilon, pw, pe, 3, 1);
toc
% profile viewer

PCinv = Polyhedron(Cinv.H, Cinv.K);
PCinv.minHRep();
Cinv = struct('H', PCinv.A, 'K', PCinv.b);

[ Ctrl, Feas ] = RMPCController( @(x,u) x'*x, epsilon, sys, N, Zs, Cinv, LN, pw, pe, 'gurobi' );

x0 = [50; 50; 0; 0];
u0 = [0; 0];
z0 = [x0; u0];
[sysk.A, sysk.B1, sysk.B2] = discmodel(Acont, Bcont, 0.02, 0.005);
epsilon_k = epsilon / sqrt(2);

Az0 = [sysk.A, sysk.B1; zeros(2, 6)]*z0;
Bk = [sysk.B2; eye(2,2)];

tic
uk = Ctrl{{z0, Az0, Bk, epsilon_k, wmax}};
toc