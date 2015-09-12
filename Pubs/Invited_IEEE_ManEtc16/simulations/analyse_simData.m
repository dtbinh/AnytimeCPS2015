%analyse data

clc;
stairs(Scheduler.time,reshape(Scheduler.signals(4).values,numel(Scheduler.time),1));