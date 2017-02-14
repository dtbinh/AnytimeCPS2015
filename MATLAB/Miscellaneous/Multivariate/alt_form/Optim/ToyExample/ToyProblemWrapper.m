% wrapper
Nruns = 51;

global rand_x0
rand_x0 = 1;
global display_on;
display_on = 0;
global robustness_max
%% SR-SQP sat mode

robustness_max = 0;

time_per_shot_SRSQP = zeros(Nruns-1,1);
robustness_one_shot_SRSQP = zeros(Nruns-1,1);
for ii = 1:Nruns
    main_example2_toy_1shot_u_param;
    if(display_on)
    pause
    end
    if(ii>1)
        time_per_shot_SRSQP(ii-1) = time_taken;
        robustness_one_shot_SRSQP(ii-1) = -fval;
    end
end
disp('Satisfaction rate')
sum(robustness_one_shot_SRSQP>=0)/numel(robustness_one_shot_SRSQP)
disp('Mean, max and std. exec time for SQSQP')
[mean(time_per_shot_SRSQP) max(time_per_shot_SRSQP) std(time_per_shot_SRSQP)]

%% BluSTL satisfaction mode

time_per_shot_BS = zeros(Nruns-1,1);
global time_1shot;
%robustness_one_shot_BS = zeros(Nruns-1,1);
for ii = 1:Nruns
    ToyExample2d;
    if(ii>1)
        time_per_shot_BS(ii-1) = time_1shot;
        if(display_on) 
            pause;
        end
        %robustness_one_shot_BS(ii) = fval;
    end
end

disp('Mean, max and std. exec time for BluSTL')
[mean(time_per_shot_BS) max(time_per_shot_BS) std(time_per_shot_BS)]
%% save data
save('Data/SatModeTimes_alwaysNot_20.mat','time_per_shot_SRSQP','time_per_shot_BS','ii');
%% SR-SQP Max Mode

robustness_max = 1;

time_per_shot_SRSQP_max = zeros(Nruns-1,1);
robustness_one_shot_SRSQP_max = zeros(Nruns-1,1);
for ii = 1:Nruns
    main_example2_toy_1shot_u_param;
    if(display_on)
    pause
    end
    if(ii>1)
        time_per_shot_SRSQP_max(ii-1) = time_taken;
        robustness_one_shot_SRSQP_max(ii-1) = -fval;
    end
end
disp('Satisfaction rate')
sum(robustness_one_shot_SRSQP_max>=0)/numel(robustness_one_shot_SRSQP_max)
disp('Mean, max and std. exec time for SQSQP in max mode')
[mean(time_per_shot_SRSQP_max) max(time_per_shot_SRSQP_max) std(time_per_shot_SRSQP_max)]
save('Data/MaxModeTimes.mat','time_per_shot_SRSQP_max');

%% plotting
load('Data/TimingSat.mat');
L = 20:10:50;
figure;
errorbar(L,[t_20_sr t_30_sr t_40_sr t_50_sr], ...
    [er_20_sr er_30_sr er_40_sr er_50_sr]);
hold all;grid on;
errorbar(L,[t_20_bs t_30_bs t_40_bs t_50_bs], ...
    [er_20_bs er_30_bs er_40_bs er_50_bs]);
xlabel('Horizon Length');
ylabel('Exec. time one shot (s)');
legend('SR-SQP','BluSTL');
title('Sat. always safe and eventually terminal');


%% plotting
L = 20:10:50;
fname_prefix = 'Data/SatModeTimes_eventually_';
for jj = 1:numel(L)
    fname_full = strcat(fname_prefix,num2str(L(jj)));
    load(fname_full);
    mean_BS(jj) = mean(time_per_shot_BS);
    er_BS(jj) = std(time_per_shot_BS);
    mean_SRSQP(jj) = mean(time_per_shot_SRSQP);
    er_SRSQP(jj) = std(time_per_shot_SRSQP);
end
figure;
errorbar(L,mean_SRSQP,er_SRSQP);hold all;
grid on;
errorbar(L,mean_BS,er_BS);hold all;
xlabel('Horizon Length');
ylabel('Exec. time one shot (s)');
legend('SR-SQP','BluSTL');
title('Sat. eventually terminal set');


%% plotting always not
L = 20:10:50;
fname_prefix = 'Data/SatModeTimes_alwaysNot_';
for jj = 1:numel(L)
    fname_full = strcat(fname_prefix,num2str(L(jj)));
    load(fname_full);
    mean_BS(jj) = mean(time_per_shot_BS);
    er_BS(jj) = std(time_per_shot_BS);
    mean_SRSQP(jj) = mean(time_per_shot_SRSQP);
    er_SRSQP(jj) = std(time_per_shot_SRSQP);
end
figure;
errorbar(L,mean_SRSQP,er_SRSQP);hold all;
grid on;
errorbar(L,mean_BS,er_BS);hold all;
xlabel('Horizon Length');
ylabel('Exec. time one shot (s)');
legend('SR-SQP','BluSTL');
title('Sat. always not unsafe set');