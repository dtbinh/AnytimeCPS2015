function [T, XT, YT, A,B,C] = monkeytits(XPoint, staliro_SimulationTime, steptime, InpSignal)
T = (0:100)';
N = length(T);
XT = rand(N,3);
YT = [XT, rand(N,1)];
A=[];
B=[];
C=[];