function [mx,CI,Int] = getMeanAndCI(x)

SEM = std(x)/sqrt(length(x));               % Standard Error
ts = tinv([0.025  0.975],length(x)-1);      % T-Score
CI = mean(x) + ts*SEM;                      % Confidence Intervals
mx = mean(x);
Int = ts*SEM;