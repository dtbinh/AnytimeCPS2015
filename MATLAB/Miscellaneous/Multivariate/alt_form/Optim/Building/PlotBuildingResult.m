%%
close all;figure;


axis([1 24 15 40]);
load('/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/Miscellaneous/Multivariate/alt_form/Optim/Building/BldgData/SatTraj.mat')
z = SimBldg(u_opt',optParams);
hold all;
plot(z(4,:),'b','linewidth',3)
hold all
plot(Sys.model_data.X(4,1:24),'--r','linewidth',3)
load('/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/Miscellaneous/Multivariate/alt_form/Optim/Building/BldgData/MaxTraj.mat')
z = SimBldg(u_opt',optParams);
hold all;
plot(z(4,:),'k','linewidth',3)
hold all
plot(Sys.model_data.X(4,1:24),'--m','linewidth',2)
load('/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/Miscellaneous/Multivariate/alt_form/Optim/Building/BldgData/Sim_hot_exact.mat')
z = SimBldg(x,optParams);
hold all;
plot(z(4,:),':g','linewidth',2);
load('/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/Miscellaneous/Multivariate/alt_form/Optim/Building/BldgData/Sim_SA_exact.mat')
z = SimBldg(x,optParams);
hold all;
plot(z(4,:),'-.c','linewidth',2);
h_legend = legend('SOP (B)','BluSTL (B)','SOP (R)','BluSTL (R)','R-SQP','SA');
set(h_legend,'FontSize',20);
P = Polyhedron('lb',[10 22],'ub',[19 28]);
plot(P,'Color','green','Alpha',0.2);
hold on;
xlabel('Time Steps (hours)','FontSize',20);
ylabel('Zone Temperature (C)','FontSize',20);
set(gca,'Xtick',1:2:24,'FontSize',20)
set(gca,'Ytick',16:2:40,'FontSize',20)

print -painters -dpdf -r600 test.pdf