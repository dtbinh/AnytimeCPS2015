%staliro_smooth_toyexample_R2
% STaliro related parameters here.

clear
clearvars -global
%load data here
load('ComfortParams.mat');

%cd('../SystemModelsAndData')

disp(' ')
disp(' Demo: A 2-d simple example ')
disp(' Press any key to continue ... ')

%pause

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
P_pred_a = Polyhedron('lb',[-1 -1],'ub',[1 1]); %The polyhedron for predicate a
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
opt.spec_space = 'Y';

opt.optimization_solver = 'SA_Taliro';
opt.optim_params.n_tests = 400;

opt


%% smooth options
clear SmoothOpt;
global taliro_SmoothRob; %flag
global SmoothOpt; %params
taliro_SmoothRob = 0;


for i = 1:numel(preds)
    SmoothOpt.preds.Sets(i).A = preds(i).A;
    SmoothOpt.preds.Sets(i).b = preds(i).b;
    SmoothOpt.preds.WavParams(i).k_min = -5;
    SmoothOpt.preds.WavParams(i).k_max = 5;
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
if(getParams) %do this once, disable flag and load params next time
    for i = 1:numel(preds)
        WavParams(i) = getWaveletParameters(SmoothOpt,genCode);
        SmoothOpt.preds.WavParams(i).E = WavParams(i).E;
        SmoothOpt.preds.WavParams(i).E_dash = WavParams(i).E_dash;
        SmoothOpt.preds.WavParams(i).D_ejk = WavParams(i).D_ejk;
        SmoothOpt.preds.WavParams(i).C_00k = WavParams(i).C_00k;
        
    end
    save('ParamsForUnitCube.mat','SmoothOpt');
else
    load('ParamsForUnitCube.mat');
end

%% also generate mex for wavelet approximation function
genCode_wavapprox = 1; %do this once, the approximation function .mex will then be used for all other purposes
if(genCode_wavapprox)     
    x_test = zeros(2,1);
    Sd_test = genWavApproxMex(SmoothOpt,x_test); %expect around 1 as the output
end

%% check signed distance computation

Smooth_signed_dist = alt_getWavApprox_vector_genable_mex([0;0],SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash) %this is the function (without the _mex) to be sped up 
taliro_SmoothRob = 0;
Actual_signed_dist = SignedDist([0;0],SmoothOpt.preds.Sets(1).A,SmoothOpt.preds.Sets(1).b)


%% check dp_taliro

%% smooth robustness
taliro_SmoothRob = 1;
SX = zeros(21,2);
ST = 0:0.2:4; ST = ST';
disp('Smooth robustness =');
dp_taliro(phi,preds,SX,ST,[],[],[])

%% actual robustness
taliro_SmoothRob = 0;
SX = zeros(21,2);
ST = 0:0.2:4; ST = ST';
disp('Actual robustness =')
dp_taliro(phi,preds,SX,ST,[],[],[])

% call the mex function that does the work
taliro_SmoothRob = 0; %exact
mx_dp_taliro(phi,preds,SX,ST)

taliro_SmoothRob = 1; %smooth
mx_dp_taliro(phi,preds,SX,ST)








