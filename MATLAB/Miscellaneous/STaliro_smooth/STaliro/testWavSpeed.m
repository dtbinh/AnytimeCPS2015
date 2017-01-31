run_matlab = 0;
nruns = 1000;
%%

if(run_matlab)
t_old = zeros(nruns,1);

for i = 1:nruns
tic;    
%profile on
alt_getWavApprox_vector_genable([0;0],SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash); %this is the function (without the _mex) to be sped up 

t_old(i) = toc;
end
%profile viewer
end
%%
if(run_matlab)
t_new = zeros(nruns,1);
for i = 1:nruns
%    profile on
    tic;
    alt_getWavApprox_vector_genable_new([0;0],SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash); %this is the function (without the _mex) to be sped up 
t_new(i) = toc;
end
%profile viewer
end
%%
if(run_matlab)
disp('m code speeds')
[mean(t_old) std(t_old)]
[mean(t_new) std(t_new)]
end
%% test mexed speeds:
if(1)
x_test = zeros(2,1);
Sd_test1 = genWavApproxMex(SmoothOpt,x_test) %expect around 1 as the output
Sd_test2 = genWavApproxMex_new(SmoothOpt,x_test) %expect around 1 as the output
end
%% old

t_old_mex = zeros(nruns,1);
for i = 1:nruns
tic;    
%profile on
alt_getWavApprox_vector_genable_mex([0;0],SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash); %this is the function (without the _mex) to be sped up 
t_old_mex(i) = toc;
end
%profile viewer

%% new
t_new_mex = zeros(nruns,1);
for i = 1:nruns
%    profile on
    tic;
    alt_getWavApprox_vector_genable_new_mex([0;0],SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash); %this is the function (without the _mex) to be sped up 
t_new_mex(i) = toc;
end
%profile viewer

%% 
disp('mex code speeds')
[mean(t_old_mex) std(t_old_mex)]
[mean(t_new_mex) std(t_new_mex)]
