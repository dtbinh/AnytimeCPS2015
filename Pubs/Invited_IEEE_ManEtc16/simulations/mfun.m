function [op] = mfun(vp,mp)
load('Data.mat'); %load the profiled data


%% 
alpha = func_it_up(vp,mp);
%alpha = 0.001;
%alpha = 0;
cost = alpha*Throughput_norm + (1-alpha)*(1./MeanPower_norm);

gpu_index = zeros(size(Throughput_norm,3),1);
cpu_index = zeros(size(Throughput_norm,3),1);
Temp = zeros(size(Throughput_norm,3),1);

for i = 1:size(Throughput_norm,3) % for all schedules
    
 Temp(i) = max(max(cost(:,:,i)));   
 [a, b] =  find(cost(:,:,i)==Temp(i));
 [a b];
 gpu_index(i) = a(1);
 cpu_index(i) = b(1); %row is gpu. col is cpu
end

[~,ix] = max(Temp);
cpu_index_best = cpu_index(ix);
gpu_index_best = gpu_index(ix);
Schedule_best = str2num(Schedule(ix,:));

tdel = Delta_90th(gpu_index_best,cpu_index_best,ix);
op = [tdel/1000 cpu_index_best gpu_index_best Schedule_best alpha];



