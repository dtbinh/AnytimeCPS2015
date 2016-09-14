Prelim = 'RobTest_N' ;
Endim = '_AnP';
%Endim = '_AnP1_or_AnP2';
Lengths = [10 20 30 50 75 100 150 250 500];
Error_mean = zeros(numel(Lengths),1);
Error_std = zeros(numel(Lengths),1);
rel_mean = zeros(numel(Lengths),1);
rel_std = zeros(numel(Lengths),1);

for i = 1:numel(Lengths)
    fname=strcat(Prelim,num2str(Lengths(i)),Endim);
    load(fname);
    if(exist('err')>0)
    Error_mean(i) = mean(err);
    Error_std(i) = std(err);
    end
    rel_mean(i) = mean(err_rel);
    rel_std(i) = std(err_rel);
    
figure(3);
hold on;
for i = 1:size(Traj_all,3)
    plot(Traj_all(1,:,i),Traj_all(2,:,i));
    hold on;
    pause(.01);
end
    
end
clc;
if(exist('err')>0)
    figure(1);
    errorbar(Lengths,(Error_mean),Error_std);
    grid on;
end
figure(2);
errorbar((Lengths),rel_mean,rel_std);
grid on;

%%


