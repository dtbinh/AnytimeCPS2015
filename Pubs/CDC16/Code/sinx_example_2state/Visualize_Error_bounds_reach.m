%
N = 5000;
e1 = e1_min + (e1_max-e1_min).*rand(N,1);
e2 = e2_min + (e2_max-e2_min).*rand(N,1);
x1_low = -pi/4;
x1_high = pi/4;
x2_low = -pi/3.25;
x2_high = -pi/5;
x1 = x1_low + (x1_high-x1_low).*rand(N,1);
x2 = x2_low + (x2_high-x2_low).*rand(N,1);

%
L = max(1,a*cos(x2_high));
E_inf_param = max([abs(e1_min),abs(e1_max),abs(e2_min),abs(e2_max)]);
E_tilde_Lip = L*Polyhedron('lb',[-E_inf_param;-E_inf_param],'ub',[E_inf_param;E_inf_param]);

%
E_tilde_Lin = Polyhedron('lb',[e1_min;a*cos(x2_high)*e2_min],'ub',[e1_max;a*cos(x2_high)*e2_max]);

%
e_tilde = [x1 a*sin(x2)] - [(x1+e1) a*sin(x2+e2)];

%% plots
figure;
%E_tilde_Lip.plot;hold on;
E_max.plot;hold on;
E_tilde_Lin.plot('Color','blue');
plot(e_tilde(:,1),e_tilde(:,2),'k.');
axis([e1_min e1_max e2_min e2_max])
h = legend('$\tilde{E}_{max}$','$\tilde{E}_{\chi}$','Randomized errors');
set(h,'Interpreter','latex');
grid on;
h = xlabel('$\tilde{e}_1$');
set(h,'Interpreter','latex');
h = ylabel('$\tilde{e}_2$');
set(h,'Interpreter','latex');
%% input
%% bounds on v
x2_idx=x2_min:.001:x2_max;
v_upper = a*(u_max+tan(x2_idx)).*cos(x2_idx);
% plot those bounds
figure;
t1=strcat('Limits on v when:  ',num2str(u_min),' <=u<= ',num2str(u_max));
title(t1);

v_lower = a*(u_min+tan(x2_idx)).*cos(x2_idx);

v_inner_upper = (u_max+tan(x2_min))*a*cos(x2_max)*ones(numel(x2_idx),1);
v_inner_lower = (u_min+tan(x2_max))*a*cos(x2_max)*ones(numel(x2_idx),1);

xlabel('x2');ylabel('v');

V_chi = getLocalVInner([],Polyhedron('lb',[x1_low;x2_low],'ub',[x1_high;x2_high]),[],Z,X,U,V_inner_global,a);
[~,maxv,minv] = getRect(V_chi)
%%
figure;
hold on;plot(x2_idx,v_upper,'b','linewidth',2);
hold on;plot(x2_idx,v_lower,'b','linewidth',2);grid on;
hold on;plot(x2_idx,v_inner_upper,'k','linewidth',2);
hold all; plot(x2_low:0.01:x2_high,ones(numel(x2_low:0.01:x2_high),1)'*maxv,'r','linewidth',2);
hold on;plot(x2_idx,v_inner_lower,'k','linewidth',2);
hold all; plot(x2_low:0.01:x2_high,ones(numel(x2_low:0.01:x2_high),1)'*-2.377,'r','linewidth',2);

h = legend('$\mathbf{v}(x_2,\overline{u})$','$\underline{v}(x_2,\underline{u})$', ...
    '$\underline{V}_{inner-global}$', ...
    '$\underline{V}_{k+j|k}$');
set(h,'Interpreter','latex');
xlabel('x_2');
ylabel('v');
%'${V_{inner-global}^{max}}$','${V_{inner-global}^{min}}$', '$\underline{V}^{max}(\chi)$', ...
%    '$\underline{V}^{min}(\chi)$');

% h = legend('$\mathbf{v}(x_2,\overline{u})$','$\underline{v}(x_2,\underline{u})$', ...
%     '${V_{inner-global}^{max}}$','${V_{inner-global}^{min}}$', '$\underline{V}^{max}(\chi)$', ...
%     '$\underline{V}^{min}(\chi)$');

