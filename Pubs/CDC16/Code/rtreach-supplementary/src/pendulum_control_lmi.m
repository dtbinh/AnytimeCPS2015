%Inverted Pendulum
%
%Fall 2008
%
%Taylor Johnson
%johnso99@nospam-illinois.edu
%University of Illinois at Urbana-Champaign
%Coordinated Science Laboratory
%Department of Electrical and Computer Engineering
%
%Linear Matrix Inequality
%
%This code utilizes the following third-party modules:
%1. YALMIP Matlab library
%   http://users.isy.liu.se/johanl/yalmip/
%   (old): http://control.ee.ethz.ch/~joloef/wiki/pmwiki.php
%2. SDPT3 Semidefinite Programming (SDP) Solver
%   http://www.math.nus.edu.sg/~mattohkc/sdpt3.html

%clear all; % let pass in arguments for system matrices, etc.

option_setup = 0; % set to 1 the first time this is called

% rerun initialization if either the yalmip functions are undefined, or the
% setup option is forced
if option_setup || ~exist('sdpvar')
    %addpath(genpath(yalmiprootdirectory));
    %addpath('D:\Dropbox\Research\rtss2014\src\lib\yalmip');
    addpath('lib\yalmip'); % relative

    addpath('lib/yalmip/extras');
    addpath('lib/yalmip/demos');
    addpath('lib/yalmip/solvers');
    addpath('lib/yalmip/modules');
    addpath('lib/yalmip/modules/parametric');
    addpath('lib/yalmip/modules/moment');
    addpath('lib/yalmip/modules/global');
    addpath('lib/yalmip/modules/robust');
    addpath('lib/yalmip/modules/sos');
    addpath('lib/yalmip/operators');

    clear classes;


    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/extras'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/demos'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules/parametric'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules/moment'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules/global'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules/robust'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/modules/sos'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/operators'));
    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/solvers/'));

    % add SDPT3 solver
    %old_dir=pwd();
    cd 'lib/SDPT3-4.0'
    addpath('lib/SDPT3-4.0');
    addpath('lib/SDPT3-4.0/dimacs');
    %addpath('lib/SDPT3-4.0/Examples');
    addpath('lib/SDPT3-4.0/HSDSolver');
    addpath('lib/SDPT3-4.0/HSDSolver/etc');
    addpath('lib/SDPT3-4.0/sdplib');
    addpath('lib/SDPT3-4.0/Solver');

    Installmex(1);
    startup;
    sqlpdemo;
    %cd old_dir;
    cd '../../'

    yalmiptest;


    %uncomment on first run to install and start solver
    %old=pwd();
    %cd 'C:\Users\tjohnson\Documents\Research\inverted_pendulum\matlab\SDPT3-4.0-beta'
    %Installmex;
    %startup;
    %cd old;

    %addpath(genpath('C:/Program Files (x86)/MATLAB/R2008a/toolbox/yalmip/solvers/yalmip2sdpa'));
    %clear classes;
end

n=4;
r=1;

A=[0         0    1.0000         0; 0         0         0    1.0000; 0   -2.7500  -10.9500    0.0043; 0   28.5800   24.9200   -0.0440];
B=[0;0;1.9400;-4.4400];

Almi=A;
Blmi=B;

thetaMin=deg2rad(-15);
thetaMax=deg2rad(15);
xMin=-0.2;
xMax=0.2;
xDotMin=-1;
xDotMax=1;
VaMin=-4.95;
VaMax=4.95;

a1=[1/xMax 0 0 0]';
a2=[1/xMin 0 0 0]';
%a3=[0 1/xDotMax 0 0]';
%a4=[0 1/xDotMin 0 0]';
a3=[0 1/thetaMax 0 0]';
a4=[0 1/thetaMin 0 0]';
%a5=[0 0 1/thetaMax 0]';
%a6=[0 0 1/thetaMin 0]';
a5=[0 0 1/xDotMax 0]';
a6=[0 0 1/xDotMin 0]';
tauS=0.002724511839376;
tauB=9.946540997091502e-004;
tauE=6.826194222571933e-004;
a7=[0 0 0 deg2rad(5)/tauS]';
a8=[0 0 0 deg2rad(-5)/tauS]';
b1=[1/VaMax];
b2=[1/VaMin];

Qlmi=sdpvar(n,n);
Ylmi=sdpvar(1,n);
Flmi=set(Qlmi > 0);
Flmi=Flmi+set(Qlmi*Almi' + Almi*Qlmi + Ylmi'*Blmi' + Blmi*Ylmi < 0);
Flmi=Flmi+set(a1'*Qlmi*a1 <= 1);
Flmi=Flmi+set(a2'*Qlmi*a2 <= 1);
Flmi=Flmi+set(a3'*Qlmi*a3 <= 1);
Flmi=Flmi+set(a4'*Qlmi*a4 <= 1);
Flmi=Flmi+set(a5'*Qlmi*a5 <= 1);
Flmi=Flmi+set(a6'*Qlmi*a6 <= 1);
%Flmi=Flmi+set(a7'*Qlmi*a7 <= 1);
%Flmi=Flmi+set(a8'*Qlmi*a8 <= 1);
Flmi=Flmi+set([eye(r) b1'*Ylmi; Ylmi'*b1 Qlmi] >= 0);
Flmi=Flmi+set([eye(r) b2'*Ylmi; Ylmi'*b2 Qlmi] >= 0);

%sdpsettings('solver','maxdet')
sdpsettings('solver','sdpt3')
sdpsettings('debug',1);

solvesdp(Flmi,-logdet(Qlmi));
Plmi=inv(double(Qlmi));
Klmi=double(Ylmi)*Plmi;

clear a7 a8;
a7=[0 0 0 deg2rad(45)/tauE]';
a8=[0 0 0 deg2rad(-45)/tauE]';
a9=[Klmi/VaMax]';
a10=[Klmi/VaMin]';

%now find area
%min logdet(Q^-1)
%s.t.: QA'+AQ<0
%      Q>0
%      aj'Qaj<=1, k=1...6
%A has to be A+BK for QA'+AQ<0
%KE=[10.0, 103.36, 27.72, 23.04];
%A2lmi=A+B*KE;
A2lmi = A+B*Klmi;
Q2lmi=sdpvar(n,n);
F2lmi=set(Q2lmi > 0);
F2lmi=F2lmi+set(Q2lmi*A2lmi'+A2lmi*Q2lmi<0);
F2lmi=F2lmi+set(a1'*Q2lmi*a1 <= 1);
F2lmi=F2lmi+set(a2'*Q2lmi*a2 <= 1);
F2lmi=F2lmi+set(a3'*Q2lmi*a3 <= 1);
F2lmi=F2lmi+set(a4'*Q2lmi*a4 <= 1);
F2lmi=F2lmi+set(a5'*Q2lmi*a5 <= 1);
F2lmi=F2lmi+set(a6'*Q2lmi*a6 <= 1);
%F2lmi=F2lmi+set(a7'*Q2lmi*a7 <= 1);
%F2lmi=F2lmi+set(a8'*Q2lmi*a8 <= 1);
F2lmi=F2lmi+set(a9'*Q2lmi*a9 <= 1);
F2lmi=F2lmi+set(a10'*Q2lmi*a10 <= 1);
solvesdp(F2lmi,-logdet(Q2lmi));
P2lmi=inv(double(Q2lmi));

i=1;
iu=1;
ip=1;
ig=1;
ib=1;
bad=0;
badPrev=0;
xStep=0.005;
xDotStep=0.01;
for (x=xMin:xStep:xMax)
    for (xdot=xDotMin:xDotStep:xDotMax)
        xi=[x 0 xdot 0]';
        if (norm(Klmi*xi) >= VaMax)
            xub(1:4,iu)=xi;
            iu=iu+1;
            bad=1;
        end;
        if (xi'*Plmi*xi > 1)
            xpb(1:4,ip)=xi;
            ip=ip+1;
            bad=1;
        end;
        if (bad==0)
            xgood(1:4,ig)=xi;
            ig=ig+1;
        end;
        if ((bad==0&&badPrev==1) || (bad==1&&badPrev==0))
            xbound(1:4,ib)=xi;
            ib=ib+1;
        end;
        i=i+1;
        badPrev=bad;
        bad=0;
    end;
end;

figure;
hold on;
plot(xgood(1:1,:),xgood(3:3,:),'bx')
plot(xpb(1:1,:),xpb(3:3,:),'g*');
plot(xub(1:1,:),xub(3:3,:),'r+');
plot(xbound(1:1,:),xbound(3:3,:),'ko');
xlabel('Position (m)');
ylabel('Velocity (m/s)');


clear xub xpb xgood xbound;
i=1;
iu=1;
ip=1;
ig=1;
ib=1;
bad=0;
badPrev=0;

%KE=[10.0, 103.36, 27.72, 23.04];
Abar1=A+B*Klmi;
%Abar1=A+B*KE;
Q=eye(4);
P1=lyap(Abar1',Q);

for (x=xMin:xStep:xMax)
    for (xdot=xDotMin:xDotStep:xDotMax)
        xi=[x 0 xdot 0]';
        if (norm(Klmi*xi) >= VaMax)
        %if (norm(KE*xi) >= VaMax)
            xub(1:4,iu)=xi;
            iu=iu+1;
            bad=1;
        end;
        if (xi'*P2lmi*xi > 1)
            xpb(1:4,ip)=xi;
            ip=ip+1;
            bad=1;
        end;
        if (bad==0)
            xgood(1:4,ig)=xi;
            ig=ig+1;
        end;
        if ((bad==0&&badPrev==1) || (bad==1&&badPrev==0))
            xbound(1:4,ib)=xi;
            ib=ib+1;
        end;
        i=i+1;
        badPrev=bad;
        bad=0;
    end;
end;
plot(xbound(1:1,:),xbound(3:3,:),'cs');

i=1;
iu=1;
ip=1;
ig=1;
ib=1;
bad=0;
badPrev=0;
xStep=0.01;
xDotStep=0.01;
for (x=thetaMin:xStep:thetaMax)
    for (xdot=-2.75:xDotStep:2.75)
        xi=[0 x 0 xdot]';
        if (norm(Klmi*xi) >= VaMax)
            xub(1:4,iu)=xi;
            iu=iu+1;
            bad=1;
        end;
        if (xi'*Plmi*xi > 1)
            xpb(1:4,ip)=xi;
            ip=ip+1;
            bad=1;
        end;
        if (bad==0)
            xgood(1:4,ig)=xi;
            ig=ig+1;
        end;
        if ((bad==0&&badPrev==1) || (bad==1&&badPrev==0))
            xbound(1:4,ib)=xi;
            ib=ib+1;
        end;
        i=i+1;
        badPrev=bad;
        bad=0;
    end;
end;

figure;
hold on;
plot(xgood(2:2,:),xgood(4:4,:),'bx')
plot(xpb(2:2,:),xpb(4:4,:),'g*');
plot(xub(2:2,:),xub(4:4,:),'r+');
plot(xbound(2:2,:),xbound(4:4,:),'ko');
xlabel('Position (m)');
ylabel('Velocity (m/s)');