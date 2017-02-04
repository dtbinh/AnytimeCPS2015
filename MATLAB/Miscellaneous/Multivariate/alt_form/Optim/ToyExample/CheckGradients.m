%%
%load('Wavparams2_j0_k10_ToyExample.mat');
dim = optParams.dim;
P_feas = AuxParams.P_feas;
P_final = AuxParams.P_final;
len = optParams.len;
P_unsafe = AuxParams.P_unsafe;
if(dim<=3)
    figure;
    plot(P_feas,'Color','gray','Alpha',0.7);
    hold on;
    plot(P_unsafe,'Color','red','Alpha',0.7);
    hold on;
    plot(P_final,'Color','green','Alpha',0.7);
    hold on;
    grid on;
end

%% for eventually;
x_pt = [1;-1]
plot(x_pt(1),x_pt(2),'*');
[f2,g2] = robustness_eventually_P(x_pt,optParams.Params_P_term,1);
sd_true = SignedDist(x_pt,optParams.P_final.A,optParams.P_final.b);
[f2 sd_true]
[g2 [robustness_eventually_P_genable_parallel(x_pt+[1;0],optParams.Params_P_term,1)-sd_true;robustness_eventually_P_genable_parallel(x_pt+[0;1],optParams.Params_P_term,1)-sd_true] ... 
    [SignedDist(x_pt+[1;0],optParams.P_final.A,optParams.P_final.b)-sd_true;SignedDist(x_pt+[0;1],optParams.P_final.A,optParams.P_final.b)-sd_true]]


%% for eventually;
clc;
x_pt = [1;1]
offset = 0.1;
plot(x_pt(1),x_pt(2),'*');
[f1,g1] = alt_getRobustnessP_and_der_vector_genable(x_pt,optParams.Params_P_unsafe,1);
f1_true = SignedDist(x_pt,optParams.P_unsafe.A,optParams.P_unsafe.b);
[f1 f1_true]
[g1 [alt_getRobustnessP_and_der_vector_genable(x_pt+offset*[1;0],optParams.Params_P_unsafe,1)-f1_true;alt_getRobustnessP_and_der_vector_genable(x_pt+offset*[0;1],optParams.Params_P_unsafe,1)-f1_true] ... 
    [SignedDist(x_pt+offset*[1;0],optParams.P_unsafe.A,optParams.P_unsafe.b)-f1_true;SignedDist(x_pt+offset*[0;1],optParams.P_unsafe.A,optParams.P_unsafe.b)-f1_true]]

%%
[f,g] = objfun2_toy_using_mex(x_0,optParams);
figure;
stairs(g);
offset = 0.1;
g_finite = zeros(numel(x_0),1);
for i = 1:optParams.dim*optParams.len
    e = zeros(size(g_finite));
    e(i) = offset;
    g_finite(i) = objfun2_toy_using_mex(x_0+offset,optParams)-;
    
end
