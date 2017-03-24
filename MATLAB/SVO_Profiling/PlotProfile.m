load('SVO_ProfilingData_perch.mat');
%% plots
figure(1);
plot(fts,abs(mean_xs),'-.o','linewidth',2,'MarkerSize',8);
hold all;
plot(fts,abs(mean_ys),'-.x','linewidth',2,'MarkerSize',8);
hold all;
plot(fts,abs(mean_zs),'-.d','linewidth',2,'MarkerSize',8);
grid on;
xlabel('# features');
ylabel('|Mean est err| (m)');
legend('x','y','z');

figure(2);
plot(fts,var_xs,'-.o','linewidth',2,'MarkerSize',8);
hold all;
plot(fts,var_ys,'-.x','linewidth',2,'MarkerSize',8);
hold all;
plot(fts,var_zs,'-.d','linewidth',2,'MarkerSize',8);
grid on;
xlabel('# features');
ylabel('Variance est err (m)');
legend('x','y','z');