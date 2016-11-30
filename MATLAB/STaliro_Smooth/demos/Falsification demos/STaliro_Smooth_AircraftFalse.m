% This is a demo for using S-TALIRO with models defined as m-functions and
% Simulated Annealing as an optimization solver

% (C) Georgios Fainekos 2010 - Arizona State Univeristy

clear
%load data here
load('ComfortParams.mat');

cd('../SystemModelsAndData')

disp(' ')
disp(' Demo: Simulated Annealing on the aircraft example from the HSCC 2010 paper. ')
disp(' Two runs will be performed for a maximum of 400 tests each. ')
disp(' Press any key to continue ... ')

pause

model = @aircraftODE;% This is a demo for using S-TALIRO with models defined as m-functions and

disp(' ')
disp('The initial conditions defined as a hypercube:')
init_cond = [200 260;-10 10;120 150] %#ok<*NOPTS>

disp(' ')
disp('The constraints on the input signals defined as a hypercube:')
input_range = [34386 53973;0 16]
disp(' ')
disp('The number of control points for each input signal:')
cp_array = [10 20];

disp(' ')
disp('The specification:')
phi = '!(<>_[0,4.0]a /\ <>_[0,4.0] b)'
preds(1).str = 'a';
disp('Type "help monitor" to see the syntax of MTL formulas')
preds(1).A = [1 0 0; -1 0 0];
preds(1).b = [250; -240];
preds(2).str = 'b';
preds(2).A = [1 0 0; -1 0 0];
preds(2).b = [240.1; -240];

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


%smooth options
clear SmoothOpt;
global taliro_SmoothRob;
global SmoothOpt;
taliro_SmoothRob = 1;


for i = 1:numel(preds)
SmoothOpt.preds.Sets(i).A = preds(i).A;
SmoothOpt.preds.Sets(i).b = preds(i).b;
SmoothOpt.preds.WavParams(i) = wavparams;
end

%special options, map everything in predicate to the 2.2 to 2.8 range
tmp = [1 240;1 250]\[2.2;2.8];
SmoothOpt.preds.Offset(1) = tmp(1);
SmoothOpt.preds.Scale(1) = tmp(2);
tmp = [1 240;1 240.10]\[2.2;2.8];
SmoothOpt.preds.Offset(2) = tmp(1);
SmoothOpt.preds.Scale(2) = tmp(2);
clear tmp;




disp(' ')
disp('Running S-TaLiRo with Simulated Annealing ...')
tic
results = staliro(model,init_cond,input_range,cp_array,phi,preds,time,opt);
toc

disp(' ')
display(['Minimum Robustness found in Run 1 = ',num2str(results.run(1).bestRob)])
display(['Minimum Robustness found in Run 2 = ',num2str(results.run(2).bestRob)])

%% sim and disp
figure(1)
clf
[T1,XT1,YT1,IT1] = SimFunctionMdl(model,init_cond,input_range,cp_array,results.run(1).bestSample,time,opt);

[aa,bb]=systemsimulator(model, results.run(1).bestSample(1:3), results.run(1).bestSample(4:end), 4, input_range, [10 30]);
T1 = aa.T;
XT1 = aa.XT;


subplot(3,1,1)
plot(T1,XT1(:,1))
title('State trajectory x_1')
subplot(3,1,2)
plot(IT1(:,1),IT1(:,2))
title('Input Signal u_1')
subplot(3,1,3)
plot(IT1(:,1),IT1(:,3))
title('Input Signal u_2')

figure(2)
clf
[T2,XT2,YT2,IT2] = SimFunctionMdl(model,init_cond,input_range,cp_array,results.run(2).bestSample,time,opt);

[aa,bb]=systemsimulator(model, results.run(2).bestSample(1:3), results.run(2).bestSample(4:end), 4, input_range, [10 30]);
T2 = aa.T;
XT2 = aa.XT;

subplot(3,1,1)
plot(T2,XT2(:,1))
title('State trajectory x_1')
subplot(3,1,2)
plot(IT2(:,1),IT2(:,2))
title('Input Signal u_1')
subplot(3,1,3)% 
plot(IT2(:,1),IT2(:,3))
title('Input Signal u_2')

cd('../Falsification demos')




%% diagnostics
disp('diagnostics')
for i = 1:numel(T1)
    r1(i) = SignedDist(XT1(i,:)',preds(1).A,preds(1).b);r2(i) = SignedDist(XT1(i,:)',preds(2).A,preds(2).b);
end
[T1 XT1(:,1) r1' r2']
pause;
% diagnostics
clear r1 r2
for i = 1:numel(T2);
    r1(i) = SignedDist(XT2(i,:)',preds(1).A,preds(1).b);r2(i) = SignedDist(XT2(i,:)',preds(2).A,preds(2).b);
end
[T2 XT2(:,1) r1' r2']