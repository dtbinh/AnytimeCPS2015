%staliro_smooth_toyexample_R2

clear
clearvars -global
%load data here
load('ComfortParams.mat');

%cd('../SystemModelsAndData')

disp(' ')
disp(' Demo: A 2-d simple example ')
disp(' Press any key to continue ... ')

pause

model = @aircraftODE;% This is a demo for using S-TALIRO with models defined as m-functions and

disp(' ')
disp('The initial conditions defined as a hyperrectangle:')

P_init = Polyhedron('lb',[-2.5 -2.5],'ub',[-1.25 2.5]);
init_cond = [-2.5 -1.25;-2.5 2.5] %#ok<*NOPTS>

disp(' ')
disp('The constraints on the input signals defined as a hyperrectangle:')
input_range = [-0.52 0.52;-0.52 0.52]
disp(' ')
disp('The number of control points for each input signal:')
cp_array = [10 10];

disp(' ')
disp('The specification:')
phi = '[]_[0,4.0]!a'
preds(1).str = 'a';
disp('Type "help monitor" to see the syntax of MTL formulas')
P_pred_a = Polyhedron('lb',[-1 -1],'ub',[1 1]);
preds(1).A = P_pred_a.A;
preds(1).b = P_pred_a.b;


disp(' ')
disp('Total Simulation time:')
time = 4

disp(' ')
disp('Create an staliro_options object with the default options:')
opt = staliro_options()

disp(' ')
disp('Change options:')
opt.runs = 2;
opt.spec_space = 'X';

opt.optimization_solver = 'SA_Taliro';
opt.optim_params.n_tests = 400;

opt


%% smooth options
clear SmoothOpt;
global taliro_SmoothRob; %flag
global SmoothOpt; %params
taliro_SmoothRob = 1;


for i = 1:numel(preds)
    SmoothOpt.preds.Sets(i).A = preds(i).A;
    SmoothOpt.preds.Sets(i).b = preds(i).b;
    SmoothOpt.preds.WavParams(i).k_min = -10;
    SmoothOpt.preds.WavParams(i).k_max = 10;
    SmoothOpt.preds.WavParams(i).j_min = 0;
    SmoothOpt.preds.WavParams(i).j_max = 1;
    SmoothOpt.preds.WavParams(i).x_min = -5;
    SmoothOpt.preds.WavParams(i).x_max = 5;
    SmoothOpt.preds.WavParams(i).dx = 0.25;
    %SmoothOpt.preds.WavParams(i) = wavparams;
end


%% get params if not loaded already
close all;
scalar_list = isPredicateScalar(SmoothOpt);
getParams = 1;
genCode = 1;
if(getParams)
    for i = 1:numel(preds)
        WavParams(i) = getWaveletParameters(SmoothOpt,genCode);
        SmoothOpt.preds.WavParams(i).E = WavParams(i).E;
        SmoothOpt.preds.WavParams(i).E_dash = WavParams(i).E_dash;
        SmoothOpt.preds.WavParams(i).D_ejk = WavParams(i).D_ejk;
        SmoothOpt.preds.WavParams(i).C_00k = WavParams(i).C_00k;
        
    end
end









