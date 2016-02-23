% Does not use fucking b4m until it has to

% For the plant given by
% dx1/dt = a*sin(x2)
% dx2/dt = -x1^2 + u
% for the feedback lin, note, y=h(x)=x1
% system has relative degree 2 in the domain x|cos(x2)~=0
% alpha(x) = tan(x2)
% beta(x) = a*cos(x2)
% u = alpha(x) + (1/beta(x))*v

%% linearized dynamics
% z = T(x) = [x1;a*sin(x2)];
clear all;
A=[0 1;0 0];
B=[0; 1];
C=eye(2);
Q = eye(size(A,2));
R = eye(size(B,2));
K_lqr = lqr(A,B,Q,R,[]);

%% nl model param and init states
x1_0 = pi/2;
x2_0 = pi/4;
a = 1;
%% set limits
% states
x1_min = -pi;
x1_max = +pi;
x2_min = -pi/3;
x2_max = +pi/3;
X = Polyhedron('lb',[x1_min;x2_min],'ub',[x1_max;x2_max]);

% error in est
e1_min = -pi/180;
e1_max = +pi/180;
e2_min = -pi/180;
e2_max = +pi/180;
E = Polyhedron('lb',[e1_min;e2_min],'ub',[e1_max;e2_max]);


% disturbance in state (xkp1 = Axk + bk + wk)
w1_min = -(pi/180)*10^(-3);
w1_max = +(pi/180)*10^(-3);
w2_min = -(pi/180)*10^(-3);
w2_max = +(pi/180)*10^(-3);
W = Polyhedron('lb',[w1_min;w2_min],'ub',[w1_max;w2_max]);

% input u
u_min = -2.75; %<1.75 and V_inner is empty
u_max = 2.75;
U = Polyhedron('lb',u_min,'ub',u_max);

% after state transform Z = T(X)
% z1 = x1 \in [x1_min, x2_max]
% z2 = a*sin(x2) \in [a_sin(x2_min),a_sin(x2_max)] since x2 domain is nice

% state limits Z for state after fb linearization
z1_min = x1_min;
z1_max = x1_max;
z2_min = a*sin(x2_min);
z2_max = a*sin(x2_max);
Z = Polyhedron('lb',[z1_min;z2_min],'ub',[z1_max;z2_max]);

% limit on inputs v
% note v = a*cos(x2)*(tan(x2)+u)
%uint = interval(u_min,u_max);
%tx2int = interval(tan(x2_min),tan(x2_max));
%acx2int = a*interval(cos(x2_max),cos(0));
%vint = acx2int*(tx2int+uint);
%V_out_shite = Polyhedron('lb',inf(vint),'ub',sup(vint)); %is this outer?
%V_conservative_in = inf(acx2int)*interval(u_min+sup(tx2int),u_max+inf(tx2int));
%V_inner_global = Polyhedron('lb',inf(V_conservative_in),'ub',sup(V_conservative_in));

V_inner_global = Polyhedron('lb',(u_min+tan(x2_max))*a*cos(x2_max),'ub',...
    (u_max+tan(x2_min))*a*cos(x2_max));
% w.c. error in z in T(xhat), zhat = z+M(x)e + O(e^2)
% M(x) = [1 0; 0 a*cos(x2)];
%tilde_e1 = interval(e1_min,e1_max);
%tilde_e2 = acx2int*interval(e2_min,e2_max);
%E_max = Polyhedron('lb',[inf(tilde_e1);inf(tilde_e2)],'ub',[sup(tilde_e1),sup(tilde_e2)]);

E_max = Polyhedron('lb',[e1_min;a*cos(0)*e2_min],'ub',[e1_max;a*cos(0)*e2_max]);

%% bounds on v
x2_idx=x2_min:.001:x2_max;
v_upper = a*(u_max+tan(x2_idx)).*cos(x2_idx);
% plot those bounds
figure;
t1=strcat('Limits on v when:  ',num2str(u_min),' <=u<= ',num2str(u_max));
title(t1);
hold on;plot(x2_idx,v_upper);
v_lower = a*(u_min+tan(x2_idx)).*cos(x2_idx);
hold on;plot(x2_idx,v_lower,'r');grid on;
v_inner_upper = (u_max+tan(x2_min))*a*cos(x2_max)*ones(numel(x2_idx),1);
v_inner_lower = (u_min+tan(x2_max))*a*cos(x2_max)*ones(numel(x2_idx),1);
hold on;plot(x2_idx,v_inner_upper,'k');
hold on;plot(x2_idx,v_inner_lower,'m');
xlabel('x2');ylabel('v');
legend('Actual upper limit','Actual lower limit','Global Inner approx lower', ...
    'Global Inner approx upper');
%% run simlunk mdl for fb lin based stabilization
%sim('asinx2model');

%% compute term set
N = 15; %Horizon
h = 1/10; %sampling

%discretization
sys = ss(A,B,C,zeros(size(A,2),size(B,2)));
sys_d = c2d(sys,.1);
Q = eye(size(A,2));
R = eye(size(B,2));
[K_lqr_d,~,~] = dlqr(sys_d.A,sys_d.B,Q,R,[]);
A_d = sys_d.A;
B_d = sys_d.B;

% fuck around with place
%[K_d_lqr,prec] = place(A_d,B_d,[0.8;0.9]);

% [Cdelta_MPT,Z_f_worst,status,tstar,fd] = GetTerminalSetZ(A_d,B_d,K_lqr_d,N,Z,V_inner_global,E_max,W);
% if(status==1||status==0)
%     figure;
%     Z.plot('Color','Blue')
%     hold on
%     Cdelta_MPT.plot('Color','yellow')
%     hold on
%     Z_f_worst.plot('Color','red')
%     legend('Z','C_{\delta}','Z_f');
%     xlabel('x_1');ylabel('x_2');
% end

%%
