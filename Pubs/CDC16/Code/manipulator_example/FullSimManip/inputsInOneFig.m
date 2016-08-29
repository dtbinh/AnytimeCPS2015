%%
figure;
plot(1:k,u_applied(1:k),'k','linewidth',2)
hold on
plot(1:k,u_max*ones(k,1),'linewidth',2,'Color','green');
hold on
%h = legend('${u_k}$','$U$');

%xlabel('Time steps k at 10Hz');
%ylabel('Input applied to plant');
%set(h,'Interpreter','latex');
grid on
%set(h,'Interpreter','latex');
axis([1 45 -11 11]);


hold on;
plot(1:k,v_applied(1:k),'*-','linewidth',2,'Color','magenta');
hold all;
mxv = zeros(k,1);
mnv = zeros(k,1);
for i = 1:k
   [~,mxv(i),mnv(i)] = getRect(V_inner_k{i});
end
[~,mxv_g,mnv_g] = getRect(V_inner_global);


plot(1:k,mxv_g*ones(k,1),'--','linewidth',2,'Color','blue');
hold all;
plot(1:k,mxv,'-.','linewidth',2,'Color','red');
hold all;

h = legend('${u_k}$','$U$', ...
    '${v_k}$','${{V}_{inner-global}}$','${{V}_{k|k}}$');
     
set(h,'Interpreter','latex');
plot(1:k,mnv_g*ones(k,1),'--','linewidth',2,'Color','blue');
hold all
plot(1:k,mnv,'-.','linewidth',2,'Color','red');
hold all;
plot(1:k,u_min*ones(k,1),'linewidth',2,'Color','green');

% h = legend('${v_k}$','${{V}_k^{max}}$','${{V}_k^{min}}$', ...
%     '${V_{inner-global}^{max}}$','${V_{inner-global}^{min}}$');

grid on;
xlabel('Time steps k at 10Hz');
ylabel('Input');
axis([1 45 -11 11]);