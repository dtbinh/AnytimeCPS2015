load('SVO_ProfilingData_perch.mat');
%% plots
figure(1);
plot(fts,abs(mean_xs),'-.o');
hold all;
plot(fts,abs(mean_ys),'-.x');
hold all;
plot(fts,abs(mean_zs),'-.d');
grid on;
xlabel('# features');
ylabel('|Mean est err| (m)');
legend('x','y','z');

figure(2);
plot(fts,var_xs,'-.o');
hold all;