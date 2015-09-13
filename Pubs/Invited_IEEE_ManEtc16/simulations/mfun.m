function [op] = mfun(vp,mp)
load('Data.mat'); %load the profiled data
% for fixed mode, makes this 1 and enter mode info later, else 0 for
% regular
mode_fix = 0;
alpha =0 ; %default
%% 
if(~mode_fix)
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
 %works
 gpu_index(i) = a(1);
 cpu_index(i) = b(1);

 %experimental
 %gpu_index(i) =min(a);
 %cpu_index(i) =min(b);
 
 %gpu_index(i) =min(b);
 %cpu_index(i) =min(a);
end

[~,ix] = max(Temp);
cpu_index_best = cpu_index(ix);
gpu_index_best = gpu_index(ix);
Schedule_best = str2num(Schedule(ix,:));

tdel = Delta_90th(gpu_index_best,cpu_index_best,ix); %works
MP = MeanPower(cpu_index_best,gpu_index_best,ix); %
%tdel = Delta_90th(cpu_index_best,gpu_index_best,ix);
op = [tdel/1000 cpu_index_best gpu_index_best Schedule_best alpha MP];
end
%% if fixed mode

if(mode_fix)
   cpuf = 6;
   gpuf = 6;
   sched = 1;
   tdel = Delta_90th(cpuf,gpuf,sched);
   Schedule_best = str2num(Schedule(sched,:));
   MP = MeanPower(cpuf,gpuf,sched);
   op = [tdel/1000 cpuf gpuf Schedule_best alpha MP];
end
