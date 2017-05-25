%load('Data_2017/SVO_profiling_Perch.mat'); %newer
%load('Data_2017/Perch_SVO.mat'); 
load('Data_2017/SVO_profiling_0.mat')
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

%%
prctl = 90;
for i = 1:numel(fts)
   
   prc_90(i) = max([prctile(Datas(i).err_x,90),prctile(Datas(i).err_y,90), ...
       prctile(Datas(i).err_z,90)]);
    
   
end
figure(3);
plot(fts,prc_90);
grid on;