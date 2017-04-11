
%%
%close all
figure;

load('Data/dataPlot.mat');

%SRSQP(B)
 hold on
plot(traj_x(1,:),traj_x(2,:),'-ko','linewidth',2,'markersize',8)
axis([-2.5 2.5 -2.5 2.5])

%BS(B)
hold on;
plot(Sys.model_data.X(1,:),Sys.model_data.X(2,:),'b*','markersize',10);grid on

%SRSQP(R)
hold on
plot(traj_x_r(1,:),traj_x_r(2,:),'-.rx','linewidth',2.5,'markersize',8)
axis([-2.5 2.5 -2.5 2.5])


%SRSQP(R,gamma=0.1)
hold on
plot(traj_x_01(1,:),traj_x_01(2,:),':md','linewidth',2.5,'markersize',8)
axis([-2.5 2.5 -2.5 2.5])

hold on
hold on;plot(traj_uni(1,:),traj_uni(2,:),'-g+','linewidth',2.5,'markersize',8)

xlabel('x_1','FontSize',20);
ylabel('x_2','FontSize',20);
%h_legend = legend('Unsafe','Terminal','SR-SQP (B)','BluSTLS (B)','SR-SQP (R)','SR-SQP (R,\gamma=0.1)');
h_legend = legend('SR-SQP (B)','BluSTLS (B)','SR-SQP (R)','SR-SQP (\gamma=0.1,\delta=0)','SR-SQP (R,unicycle)');
set(h_legend,'FontSize',20);
grid off
set(gca,'Xtick',-2.5:2.5:2.5,'FontSize',20)
set(gca,'Ytick',-2.5:2.5:2.5,'FontSize',20)

P_unsafe = Polyhedron('lb',[-1 -1],'ub',[1 1]);
P_final = Polyhedron('lb',[2 2],'ub',[2.5 2.5]);
plot(P_unsafe,'Color','red','Alpha',0.7);
hold on;
plot(P_final,'Color','green','Alpha',0.7);
hold on;