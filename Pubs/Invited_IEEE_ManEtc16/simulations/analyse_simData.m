

%analyse data
load Data.mat
clc;
%stairs(Scheduler.time,reshape(Scheduler.signals(2).values,numel(Scheduler.time),1));


%which schedule
Schedule_pick = reshape(Scheduler.signals(4).values,numel(Scheduler.time),1);
CPUF_pick = reshape(Scheduler.signals(2).values,numel(Scheduler.time),1);
GPUF_pick = reshape(Scheduler.signals(3).values,numel(Scheduler.time),1);

%i(t),j(t),k(t) are gpu freq index, cpu freq index, schedule index at time t
i = zeros(length(Scheduler.time),1);
j = zeros(length(Scheduler.time),1);
k = zeros(length(Scheduler.time),1);
Power = zeros(length(Scheduler.time),1);
CPU_F = zeros(length(Scheduler.time),1);
GPU_F = zeros(length(Scheduler.time),1);

for t = 1:length(Scheduler.time) % for all sim times
    for sch = 1:size(Schedule,1) %find which CPU-GPU schedule was picked
        if(Schedule_pick(t) == str2num(Schedule(sch,:)))
            k(t) = sch;
        end
    end
    i(t) = CPUF_pick(t);
    j(t) = GPUF_pick(t);
    
    Power(t) = MeanPower(i(t),j(t),k(t));
    CPU_F(t) = CPU_freq(i(t),1);
    GPU_F(t) = GPU_freq(j(t),1);
end

stairs(Scheduler.time,Power)
figure
stairs(Scheduler.time,CPU_F)
hold all
stairs(Scheduler.time,GPU_F)
figure;
plot(SysOut.signals(3).values,SysOut.signals(4).values);
ControlCost = sum(SysOut.signals(3).values.^2)
kk = reshape(ScopeData.signals(3).values,numel(ScopeData.time),1);
'Energy'
kk(end)
length(SysOut.time)

