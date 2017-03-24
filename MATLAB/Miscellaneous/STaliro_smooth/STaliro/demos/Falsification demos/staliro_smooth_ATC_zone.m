%staliro_smooth_toyexample_R2
% STaliro related parameters here.

clc;
clear all
%load data here
% load the wavparams for a unit square in R2
load('ParamsForUnitCube.mat','SmoothOpt');
global SmoothOpt
WavParams = SmoothOpt.preds.WavParams;
clear SmoothOpt
clearvars -global

%cd('../SystemModelsAndData')

disp('Fuck you!')


%pause


disp(' ')
disp('The specification:')
phi = '[]_[0,4.0]!P1'

disp('Type "help monitor" to see the syntax of MTL formulas')

%Predicates
ChicagoTermAirspace;

preds(1).str = 'P1';
preds(1).A = P1.A;
preds(1).b = P1.b;
preds(2).str = 'P2';
preds(2).A = P2.A;
preds(2).b = P2.b;
preds(3).str = 'P3';
preds(3).A = P3.A;
preds(3).b = P3.b;
% preds(4).str = 'Po1';
% preds(4).A = Pouter_1.A;
% preds(4).b = Pouter_1.b;
% preds(5).str = 'Po1';
% preds(5).A = Pouter_2.A;
% preds(5).b = Pouter_2.b;


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
disp('Init SmoothOpt ...')
clear SmoothOpt;
global taliro_SmoothRob; %flag
%global SmoothOpt; %params
taliro_SmoothRob = 0; %so that signed distance doesn't mess up yet


for i = 1:numel(preds)
    SmoothOpt.preds.Sets(i).A = preds(i).A;
    SmoothOpt.preds.Sets(i).b = preds(i).b;
    SmoothOpt.preds.WavParams(i) = WavParams; %inherit from square
    %since squares here;
    
end
for i = 1:numel(preds)
    SmoothOpt.preds.WavParams(i).Scale = max(abs(preds(i).b));
    SmoothOpt.preds.WavParams(i).Offset = zeros(2,1);
end
%% generate mex for wavelet approximation function
disp('Gen wav approx mex ...')
genCode_wavapprox = 0; %do this once, the approximation function .mex will then be used for all other purposes
if(genCode_wavapprox)     
    x_test = 2*ones(2,1);
    Sd_test = genWavApproxMex(SmoothOpt,x_test); %expect around 1 as the output
end




%% check signed distance computation
x_test = [0;0];
Smooth_signed_dist = alt_getWavApprox_vector_genable_mex(x_test,SmoothOpt.preds.WavParams(1).C_00k,SmoothOpt.preds.WavParams(1).D_ejk, ...
    SmoothOpt.preds.WavParams(1).k_min,SmoothOpt.preds.WavParams(1).k_max, ...
    SmoothOpt.preds.WavParams(1).j_min,SmoothOpt.preds.WavParams(1).j_max, ...
    SmoothOpt.preds.WavParams(1).E_dash) %this is the function (without the _mex) to be sped up 

Actual_signed_dist = SignedDist(x_test,SmoothOpt.preds.Sets(1).A,SmoothOpt.preds.Sets(1).b)


%% check dp_taliro

% smooth robustness
taliro_SmoothRob = 1;
SX = zeros(21,2);
ST = 0:0.2:4; ST = ST';
disp('Smooth robustness =');
dp_taliro(phi,preds,SX,ST,[],[],[])

% actual robustness
taliro_SmoothRob = 0;
SX = zeros(21,2);
ST = 0:0.2:4; ST = ST';
disp('Actual robustness =')
dp_taliro(phi,preds,SX,ST,[],[],[])








