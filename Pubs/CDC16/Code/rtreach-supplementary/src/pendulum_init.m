%clear all;



theta_min_deg=-30;  %degrees
theta_max_deg=30;   %degrees
theta_min_rad=deg2rad(theta_min_deg);   %radians
theta_max_rad=deg2rad(theta_max_deg);   %radians
%x_min=-0.7;         %meters
%x_max=0.7;          %meters
x_min=-0.2;         %meters
x_max=0.2;          %meters
xdot_min=-1;        %meters/second
xdot_max=1;         %meters/second
va_min=-4.95;       %volts
va_max=4.95;        %volts

%
u_sat_max = va_max;
u_sat_min = va_min;


Ts=0.020;
%Tc=0.020;   %20ms control period
Tc = 0.001;
fs=1/Ts;
fc=1/Tc;

syms x1 x2 x3 x4;     %state variables
syms x01 x02 x03 x04; %initial conditions
syms a22 a23 a24 a42 a43 a44; %system matrix
syms a22w a23w a24w a42w a43w a44w; %system matrix
syms b2 b4; %control matrix
syms Va;

%physical parameters
g=-9.8; %gravity: -9.8 m/s
m=1;    %mass
Ki=0.9; %torque constant
Kb=0.9; %back-emf constant
Kg=1;   %gear ratio
r=2; %
Ra=0.95;    %armature resistance
Bm=1.95;    %
Btheta=0.95;    
Bbar=((Kg*Bm)/(r^2))+(((Kg^2)*Ki*Kb)/((r^2)*Ra));
Bl=((Kg*Ki)/(r*Ra));
M=5;    %mass
Jm=5;   %moment of inertia
l=0.5;  %length
Mbar=m+M+(Kg*Jm)/(r^2); %effective mass
Dl=(4*Mbar)-3*m;

X0s=[x01 x02 x03 x04]';
X=[x1 x2 x3 x4];
U=[Va];
%As=[0 1 0 0; 0 -a22 -a23 a24; 0 0 0 1; 0 a42 a43 -a44];
As=[0 0 1 0; ; 0 0 0 1; 0 -a22 -a23 a24; 0 a42 a43 -a44];
Asw=[0 1 0 0; 0 -a22w -a23w a24w; 0 0 0 1; 0 a42w a43w -a44w];
%Bs=[0; b2; 0; -b4];
Bs=[0; 0; b2; -b4];
%a22=0.1;  a23=0.01;    a24=0.01;  a42=0.01;  a43=0.5;  a44=0.1;
%a22w=(4*Bbar)/(Dl);  a23w=(3*m*g)/(Dl);   a24w=(6*Btheta)/(l*Dl);
%a42w=(6*Bbar)/(l*Dl);    a43w=(6*Mbar*g)/(l*Dl);  a44w=(12*Mbar*Btheta)/(m*(l^2)*Dl);
a22=2.75; a23=10.95; a24=0.0043; a42=28.58; a43=24.92; a44=0.044; %real matrix

%Xreal=[x theta xdot thetadot]'

%b2=0.1;   b4=0.5;
%b2=(4*Bl)/(Dl); b4=(6*Bl)/(l*Dl);
b2=1.94; b4=4.44; %real matrix
%x1=x, x2=x', x3=theta, x4=theta'
%x01=0.1; x02=0.2; x03=0.5; x04=-0.5;
%x01=0.05; x02=0.05; x03=0.05; x04=0.05; %interesting plot: edge of safety
%area
%x01=0.05; x02=0.05; x03=-0.05; x04=0.05;
%x01=0.1; x02=0.15; x03=0.05; x04=0.05;
%x01=0.05; x02=0.05; x03=-0.1; x04=-0.1; %edge of larger safety
%x01=-0.15; x02=-0.21; x03=0.4; x04=1.25;
%x01=-0.19; x02=-0.2418; x03=0.3; x04=1.41; %extrema safety
x01=-1; x02=-0.2581; x03=0.13; x04=1.17; %extrema experimental

A=eval(As);
Aw=eval(Asw);
B=eval(Bs);
X0=eval(X0s);

%A=[37.62, 58.22, 17.87, 11.61; 58.22, 313.16, 69.36, 56.09; 17.87, 69.36, 29.81, 14.81; 11.61, 56.09, 14.81, 12.04];
%A=[1 -0.00051281 0.017961 -0.0000026781; 0 1.0056 0.0046419 0.020029; 0 -0.049519 0.80322 -0.00043546; 0 0.55967 0.44824 1.0048;]

%B=[0.0003618; -0.00082708; 0.034913; -0.079879];

Q=eye(4); %positive definite Q
syms p11 p12 p13 p14 p22 p23 p24 p33 p34 p44;
P=[p11 p12 p13 p14; p12 p22 p23 p24; p13 p23 p33 p34; p14 p24 p34 p44];

%linear state feedback control: V_a=KX=inv(-R)B'SX
%A'S+SA-SBinv(R)B'S+D=0
%R1=0.01
%R2=0.01
%D=eye(4)

syms KS1 KS2 KS3 KS4 KB1 KB2 KB3 KB4 KE1 KE2 KE3 KE4;
%KS=[7.6,  13.54, 42.85,  8.25];     %safety
%KS=[6.0, 20.0, 60.0, 16.0];         %safety (real system)
KS=[7.6,  42.85, 13.54,  8.25];     %safety
KSs=[KS1, KS2, KS3, KS4];           %safety symbolic
%KB=[3.16, 19.85, 69.92,  14.38];    %baseline
%KB=[8.0, 32.0, 120.0, 12.0];        %baseline (real system)
KB=[3.16, 69.92, 19.85,  14.38];    %baseline
KBs=[KB1, KB2, KB3, KB4];
%KE=[10.0, 27.72, 103.36, 23.04];    %experimental
%KE=[5.7807, 42.2087, 14.0953, 8.6016];
KE=[10.0, 103.36, 27.72, 23.04];    %experimental
%KE=[10.0, 36.0, 140.0, 14.0];       %experimental (real system)
KEs=[KE1, KE2, KE3, KE4];

%from lmi
Plmi=[38.3367   26.2506    8.6703    4.7515; 26.2506   56.5561   15.2589    8.6971; 8.6703   15.2589    6.6481    3.2088; 4.7515    8.6971    3.2088    1.8244];
%Klmi=[7.2671   30.1022   11.7542    5.9111];
%KS=Klmi;
det(Plmi); %must be greater than 0 (shows P is positive definite)

%Xdot=Abar*X
AbarS=A+B*KS;
AbarSs=As+Bs*KSs;
AbarB=A+B*KB;
AbarE=A+B*KE;

det(AbarS'*Plmi+Plmi*AbarS); %must be less than 0 (shows positive negative, and shows lyapunov derivative is negative always)
det(AbarB'*Plmi+Plmi*AbarB); %must be less than 0 (shows positive negative, and shows lyapunov derivative is negative always)
det(AbarE'*Plmi+Plmi*AbarE); %must be less than 0 (shows positive negative, and shows lyapunov derivative is negative always)

C=[0 1 0 1];
sysS=ss(A,B*KS,C,0);
sysB=ss(A,B*KB,C,0);
sysE=ss(A,B*KE,C,0);
%figure;
%nyquist(sysS);
%hold on;
%nyquist(sysB);
%nyquist(sysE);
%legend('Safety', 'Baseline', 'Experimental');

sysdS=ss(A,B*KS,C,0,Tc);
sysdB=ss(A,B*KB,C,0,Tc);
sysdE=ss(A,B*KE,C,0,Tc);
%figure;
%nyquist(sysdS);
%hold on;
%nyquist(sysdB);
%nyquist(sysdE);
%legend('Safety', 'Baseline', 'Experimental');

%syms t;
%Abarexpm=expm(AbarS*t);

eigAbarS=eig(AbarS)
eigAbarB=eig(AbarB)
eigAbarE=eig(AbarE)

%Lyapunov and Discrete Lyapunov Equations for each System
P3=lyap(AbarS',Q)
PD3=dlyap(AbarS',Q)
P2=lyap(AbarB',Q)
PD2=dlyap(AbarB',Q)
P1=lyap(AbarE',Q)
PD1=dlyap(AbarE',Q)

SPtBad=0;
SPdtBad=0;

%set up for previous state (for switching)
Sxtmp=X0;
Sutmp=0;

Bxtmp=X0;
Butmp=0;

Extmp=X0;
Eutmp=0;

SwRxtmp=X0;
SwRutmp=0;

fSwRxtmp=X0;
fSwRutmp=0;

%Timing is crucial to our simulation here.  We use the given control cycle
%time of Tc=20ms to control the main operation (that is, the control is 
%updated every 20ms), then tdiv is the number of
%subsamples to also model within this main period, so that we have smoother
%trajectories within this larger control cycle.
tcyc=Tc;
tdiv=30; %minimum is 1 (1 division per control cycle, same as only looking at control cycle)
tmax=5;
time_ctrl=[0:tcyc:tmax]';      %vector of control cycle times
time_traj=[0:tcyc/tdiv:tmax]'; %vector of trajectories

%these are constants
F=expm(A*Tc);
Ft=expm(A*(tcyc/tdiv));
PF=lyap(F,-Q);
%F=A*Tc;
syms tau;
%G=int(expm(A*tau),tau,0,Tc);
%G=A*(expm(A*Tc)-eye(4)); %int(expm(A*tau),tau,0,Tc)=A*expm(A*tau)|0,Tc=A*(expm(A*T)-expm(A*0))=A*(expm(A*T)-I)
%[v,d]=eig(A);
%G=eval(int((v*diag(exp(diag(d)))/v)*tau,0,Tc));
G=pinv(A)*(expm(A*Tc)-eye(4));
Gt=pinv(A)*(expm(A*(tcyc/tdiv))-eye(4));
%G=inv(A)*((A*Tc)-eye(4));
%from mathematica:
%G=[0.02, 0.000199867, -1.32935*10^-8, 1.32535*10^-8; 4.38118*10^-19,
%0.01998, -1.99204*10^-6, 1.98405*10^-6;7.78952*10^-21, 1.33201*10^-8,
%0.0200007, 0.00019987; 1.47391*10^-20, 1.99737*10^-6, 0.0000999349, 0.0199807];

Sxtmpi=Sxtmp;

cS=norm(P3*B,inf)/(min(eig(Q)));
dS=norm(KS*A,inf)+norm(KS*B*KS,inf);
tauS=1/(cS*dS);

cB=norm(P2*B,inf)/(min(eig(Q)));
dB=norm(KB*A,inf)+norm(KB*B*KB,inf);
tauB=1/(cB*dB);

cE=norm(P1*B,inf)/(min(eig(Q)));
dE=norm(KE*A,inf)+norm(KE*B*KE,inf);
tauE=1/(cE*dE);

Sxtmpp=[0 0 0 0]'; %starting
Sxtmppp=[0 0 0 0]';

St(1:4,1)=X0;
Bt(1:4,1)=X0;
Et(1:4,1)=X0;
Swt(1:4,1)=X0;


%pendulum_control_lmi;




%[SPlmi,Sxbound1,Sxbound2]=pendulum_roa(A, B, KS, 0, 0);
%[BPlmi,Bxbound1,Bxbound2]=pendulum_roa(A, B, KB, 0, 0);
%[EPlmi,Exbound1,Exbound2]=pendulum_roa(A, B, KE, 0, 0);

% figure;
% hold on;
% plot(Sxbound1(1:1,:),Sxbound1(3:3,:),'bo');
% plot(Bxbound1(1:1,:),Bxbound1(3:3,:),'g*');
% plot(Exbound1(1:1,:),Exbound1(3:3,:),'k+');
% title('Stabilizable Regions for x and xDot');
% legend('Safety', 'Baseline', 'Experimental');
% xlabel('x (m)');
% ylabel('xDot (m/s)');
% 
% figure;
% hold on;
% plot( radtodeg(Sxbound2(2:2,:)), radtodeg(Sxbound2(4:4,:)),'bo');
% plot( radtodeg(Bxbound2(2:2,:)), radtodeg(Bxbound2(4:4,:)),'g*');
% plot( radtodeg(Exbound2(2:2,:)), radtodeg(Exbound2(4:4,:)),'k+');
% title('Stabilizable Regions for \theta and \theta Dot');
% legend('Safety', 'Baseline', 'Experimental');
% xlabel('\theta (deg)');
% ylabel('\theta Dot (deg/s)');
% 
% clear P;
% P(:,:,1) = P1;
% P(:,:,2) = P2;
% P(:,:,3) = P3;
% 
% k(:,1) = KS;
% k(:,2) = KB;
% k(:,3) = KE;

% WRONG MATRICES
%A = [0 1 0 0;0 -10.95 -2.75 0.0043; 0 0 0 1; 0 24.92 28.58 -0.044];
%B = [0; 1.94; 0; -4.44];
%P = cat(3,[1.8030 2.3010 0.8447 0.3839; 2.3010 10.0825 2.8171 1.4036; 0.8447 2.8171 1.0109 0.4782; 0.3839 1.4036 0.4782 0.2606], [2.6836 2.7166 1.1849 0.5533; 2.7166 10.0974 3.0287 1.4297; 1.1849 3.0287 1.1695 0.5365; 0.5533 1.4297 0.5365 0.2645], [1.6987 1.8877 0.7664 0.3461; 1.8877 8.8812 2.5537 1.1747; 0.7664 2.5537 0.9601 0.431; 0.3461 1.1747 0.4318 0.2050]);
%k(:,1) = [6 20 60 16];
%k(:,2) = [8 32 120 12];
%k(:,3) = [10 36 140 14];





% FROM STAN

A = [0 1 0 0 ;
    0 -10.95 -2.75 0.0043 ;
    0 0 0 1 ;
    0 24.92 28.58 -0.044
    ];

B = [0 ; 1.94 ; 0 ; -4.44 ];

K_lmi = [  0.4072,  7.2373, 18.6269,   3.6725  ];

K = K_lmi;
k(:,1) = K;

% x vector: position, theta, velocity, omega

P_lmi = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];
% row swap
% P_lmi = [
%     1.0520    1.2082    0.2580    0.1988 ;
%     0.2580    4.6631    2.2108    1.0090 ;
%     1.2082   33.9334    4.6631    4.0269 ;
%     0.1988    4.0269    1.0090    0.8424 ];

P(:,:,1) = P_lmi;

eig(A + B*K)

[SPlmi,Sxbound1,Sxbound2]=pendulum_roa(A, B, K, 0, 0, P_lmi);

figure;
hold on;
plot(Sxbound1(1:1,:),Sxbound1(3:3,:),'go');


% uniform scaling of ellipse
%lambda = 1.005; % worked for some at least
%lambda = 1.01; % also worked
%lambda = 1.02; % also worked
%lambda = 1.02025; % worked
%lambda = 1.020375; % worked

%lambda = 1.0204; % worked, trying this
%lambda = 1.0;

lambda = 1.05;

%lambda = 1.020425; % failed
%lambda = 1.02045; % failed
%lambda = 1.0205; % failed
%lambda = 1.02125; % failed
%lambda = 1.0225; % failed for many
%lambda = 1.025; % failed for many

%lambda = 1.05; % failed

plot(lambda.*Sxbound1(1:1,:),lambda.*Sxbound1(3:3,:),'mo');
plot_potential;
title('Stabilizable Regions for x and \dot{x}');
%legend('Safety', 'Baseline', 'Experimental');
xlabel('x (m)');
ylabel('\dot{x} (m/s)');

figure;
hold on;
plot( radtodeg(Sxbound2(2:2,:)), radtodeg(Sxbound2(4:4,:)),'go');
plot(lambda.*radtodeg(Sxbound2(2:2,:)),lambda.*radtodeg(Sxbound2(4:4,:)),'mo');
plot_potential_angle;
title('Stabilizable Regions for \theta and \dot{\theta}');
%legend('Safety', 'Baseline', 'Experimental');
xlabel('\theta (deg)');
ylabel('\dot{\theta} (deg/s)');

idx_x = 1;
idx_v = 3;
idx_theta = 2;
idx_omega = 4;

option_external_ic = 1; % use from other simulator

if ~option_external_ic
    x_init = [lambda.*Sxbound1(idx_x:idx_x,:), lambda.*Sxbound2(idx_x:idx_x,:);];
    v_init = [lambda.*Sxbound1(idx_v:idx_v,:), lambda.*Sxbound2(idx_v:idx_v,:);];
    theta_init = [lambda.*Sxbound1(idx_theta:idx_theta,:), lambda.*Sxbound2(idx_theta:idx_theta,:);]; % keep rad
    omega_init = [lambda.*Sxbound1(idx_omega:idx_omega,:), lambda.*Sxbound2(idx_omega:idx_omega,:);]; % keep rad
end

% original
x0 = [-0.170; -0.258; 0.130; 1.170];
% from stan's code:
%x0 = [-0.1; 0.9; 0; 0]; % unstable
%x0 = [-0.1; 0.8; 0; 0]; % stable










% check x'px >= 1
% x = -0.1, v = 0.8, 0, 0


Tmax = 20; % TODO: check and add a checker to see if unstable to classify runs
xTerminate = 20; % max norm of state to quit at (presume going unstable)
%xTerminateMin = 1e-4; % min norm to terminate (i.e., if so small, is probably converged to 0)
xTerminateMin = 0.02;