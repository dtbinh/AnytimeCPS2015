%Sim Main
Prelims_no_b4m; %init everything
load('TempSets_par.mat');
%init state for linearized system
z0 = T_diffeo([x1_0;x2_0],a);
x0 = T_inv_diffeo(z0,a);
if(x0~=[x1_0;x2_0]) %sanity check
   'Something is off' 
end
%init estimate of x0
x0_hat = x0 + (mag)*(pi/180)*rand(numel(x0),1); %x0_hat = x0 + e0
z0_hat = T_diffeo(x0_hat,a);
%get reach set for x0 with error in there
X_0 = plus(x0,-E);
X_0.minHRep;