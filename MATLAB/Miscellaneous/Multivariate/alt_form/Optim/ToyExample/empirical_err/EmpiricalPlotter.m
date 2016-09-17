Prelim = 'RobTest_N' ;
%Endim = '_P1_until_P2';
%Endim = '_AnP1_or_AnP2';
%Endim = '_AnP';
Endim = '_AnP1_and_AnP2';
Lengths = [10 20 30 50 75 100 150 250 500];
Error_mean = zeros(numel(Lengths),1);
Error_std = zeros(numel(Lengths),1);
Error_var = zeros(numel(Lengths),1);
rel_mean = zeros(numel(Lengths),1);
rel_std = zeros(numel(Lengths),1);
err_rmse = zeros(numel(Lengths),1);
for i = 1:numel(Lengths)
    fname=strcat(Prelim,num2str(Lengths(i)),Endim);
    load(fname);
    if(exist('err')>0)
    Error_mean(i) = mean(err);
    Error_std(i) = std(err);
    Error_var(i) = var(err);
    err_rmse(i) = sqrt(sum(err.^2))/numel(err);
    
    end
    rel_mean(i) = mean(err_rel);
    rel_std(i) = std(err_rel);
    
figure(3);
hold on;
for i = 1:size(Traj_all,3)
    plot(Traj_all(1,:,i),Traj_all(2,:,i));
    hold on;
    pause(.001);
end
    
end
clc;
if(exist('err')>0)
    figure(1);
    errorbar(Lengths,abs(Error_mean),Error_std);
    grid on;
    xlabel('Trajectory length');
    ylabel('mean and std err');
    figure(4);
    errorbar(Lengths,err_rmse,Error_var);
    grid on;
    xlabel('Trajectory length');
    ylabel('rmse and var err');
end
figure(2);
errorbar((Lengths),rel_mean,rel_std);
grid on;
xlabel('Trajectory length');
ylabel('Relative err mean and std');


%%
if(0) %for the P1 until P2 data
   load('RobTest_N250_P1_until_P2');
   figure(1);
   hold on;errorbar(250,abs(mean_err),std_err);
   figure(2);
   hold on;errorbar(250,mean_err_rel,std_err_rel)
end

