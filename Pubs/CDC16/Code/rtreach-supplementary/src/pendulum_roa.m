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

function [P, xbound1, xbound2] = pendulum_roa(A, B, K, stateBound, controlBound, Plmi)
    n=4;
    r=1;
    
    option_resolve = 0; % resolve lmis?
    
    option_saturation = 0; % add saturation constraint?

    Almi=A;
    Blmi=B;
    Klmi=K;

    thetaMin=deg2rad(-20);
    thetaMax=deg2rad(20);
    
    thetaDotMin = -3;
    thetaDotMax = 3;
    
    xMin=-1.25;
    xMax=1.25;
    xDotMin=-2.05;
    xDotMax=2.05;
    
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
    a7=[Klmi/VaMax]';
    a8=[Klmi/VaMin]';
    b1=[1/VaMax];
    b2=[1/VaMin];

    %now find area
    %min logdet(Q^-1)
    %s.t.: QA'+AQ<0
    %      Q>0
    %      aj'Qaj<=1, k=1...6
    %A has to be A+BK for QA'+AQ<0
    
    if option_resolve
        A2lmi=Almi+Blmi*Klmi;
        Q2lmi=sdpvar(n,n);
        F2lmi=set(Q2lmi > 0);
        F2lmi=F2lmi+set(Q2lmi*A2lmi'+A2lmi*Q2lmi<0);
        F2lmi=F2lmi+set(a1'*Q2lmi*a1 <= 1);
        F2lmi=F2lmi+set(a2'*Q2lmi*a2 <= 1);
        F2lmi=F2lmi+set(a3'*Q2lmi*a3 <= 1);
        F2lmi=F2lmi+set(a4'*Q2lmi*a4 <= 1);
        F2lmi=F2lmi+set(a5'*Q2lmi*a5 <= 1);
        F2lmi=F2lmi+set(a6'*Q2lmi*a6 <= 1);
        F2lmi=F2lmi+set(a7'*Q2lmi*a7 <= 1);
        F2lmi=F2lmi+set(a8'*Q2lmi*a8 <= 1);
        solvesdp(F2lmi,-logdet(Q2lmi));
        P2lmi=inv(double(Q2lmi));
    else
        P2lmi = Plmi; % from input
    end

    % x and v
    
    i=1;
    iu=1;
    ip=1;
    ig=1;
    ib=1;
    bad=0;
    badPrev=0;
    xStep=0.01;
    xDotStep=0.01;
    for (x=xMin:xStep:xMax)
        for (xdot=xDotMin:xDotStep:xDotMax)
            xi=[x 0 xdot 0]';
            if option_saturation
                 if (norm(Klmi*xi) >= VaMax)
                     xub(1:4,iu)=xi;
                     iu=iu+1;
                     bad=1;
                 end;
            end
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
                xbound1(1:4,ib)=xi;
                ib=ib+1;
            end;
            i=i+1;
            badPrev=bad;
            bad=0;
        end;
    end;

    % theta and omega
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
        for (xdot=thetaDotMin:xDotStep:thetaDotMax)
            xi=[0 x 0 xdot]';
            if option_saturation
                 if (norm(Klmi*xi) >= VaMax)
                     xub2(1:4,iu)=xi;
                     iu=iu+1;
                     bad=1;
                 end;
            end
            if (xi'*P2lmi*xi > 1)
                xpb2(1:4,ip)=xi;
                ip=ip+1;
                bad=1;
            end;
            if (bad==0)
                xgood2(1:4,ig)=xi;
                ig=ig+1;
            end;
            if ((bad==0&&badPrev==1) || (bad==1&&badPrev==0))
                xbound2(1:4,ib)=xi;
                ib=ib+1;
            end;
            i=i+1;
            badPrev=bad;
            bad=0;
        end;
    end;
    
    %cut off first element
    xbound1=xbound1(:,2:end);
    xbound2=xbound2(:,2:end);
    P=P2lmi;
end