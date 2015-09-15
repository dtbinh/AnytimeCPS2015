

%analyse data
load Data.mat

%stairs(Scheduler.time,reshape(Scheduler.signals(2).values,numel(Scheduler.time),1));
faragasso_params;
sim('sim_ieee');

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

figure(1)
stairs(Scheduler.time,Power); hold all;grid on;
figure(2);
stairs(Scheduler.time,CPU_F); 
hold all; grid on;
stairs(Scheduler.time,GPU_F);hold all
figure(3);
plot(SysOut.signals(3).values,SysOut.signals(4).values);hold all; grid on;




% ControlCost = sum(abs(SysOut.signals(3).values))/numel(SysOut.signals(3).values)
 controlcostInt = ScopeData.signals(1).values(end)
 kk = reshape(ScopeData.signals(3).values,numel(ScopeData.time),1);
 'Energy'
 kk(end)
% length(SysOut.time)

