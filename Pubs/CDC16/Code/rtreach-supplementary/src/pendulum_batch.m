%
% script for batch executing simulations of stateflow models
%

%clc; % bad on new laptop...

clear all; close all;

%bdclose('all'); % close all block diagrams (uncoditionally, careful in case not saved!)

% parse input arguments for options
%

% parameters:
% minimum N
% maximum N
% minimum failures
% maximum failures
% random failures? (1/0)



option_batch = 1; % run many simulations (batch processing)
option_parallel = 0; % run simulations in parallel
option_regenerate = 1; % regenerate Simulink/Stateflow models (else can reuse already generated models)
option_messages = 1; % display messages to user (slower, but informs of progress)

warning('off','all'); % disable all warnings (disconnected ports, etc.)

path_output_model = 'model/';
path_output_data = 'data/';
path_output_image = 'image/';
%path_output_compilation = 'bin/';
path_output_compilation = '';

% set simulink binary file directory (compilation output)
% see: http://www.mathworks.com/help/rtw/ref/simulink.filegencontrol.html
% also see: http://www.mathworks.com/help/rtw/ug/control-the-location-for-generated-files.html
Simulink.fileGenControl('set', 'CacheFolder', path_output_compilation, 'CodeGenFolder', path_output_compilation);


% http://www.mathworks.com/videos/running-multiple-simulink-simulations-in-parallel-68946.html
if option_parallel
    %matlabpool local 4 % more details: http://www.mathworks.com/help/simulink/ug/running-parallel-simulations.html
    if isempty(gcp)
        parpool(4);
    end
    %global simout;
    global secInDay;
    global secInWeek;
end



iteration_step = 1; % probably needs to be 1 unless change some other parts



formatOut = 'yyyy-mm-dd_HH-MM-SS';
if option_messages
    startTime = datestr(now, formatOut);
    ['starting simulation at ', startTime]
end
time_simstart = tic % start timer for runtime analysis


%TODO: may have to disable this
%set_param('dc2dc','MaxConsecutiveZCsMsg','none')

if option_parallel
    apool = gcp();
    % todo: add models
end

for N = 1
    Ni = N;
    ID = [1:N];
    Nfi = 1; % for indexing arrays, etc (since Nmin may not start at first array entry)
    
    % update user on status
    if option_messages
        ['N=', num2str(N), ' starting at ', datestr(now, formatOut)]
    end

    %sysname = ['bmgen_array_N',num2str(N)]; % TODO: add suffix based on parameters
    %sys_filename = [sysname, '.mdl'];
    sysname = 'pendulum';
    sys_filename = [sysname, '.slx'];

    % TODO: double check if possible to just call array_init again without reinitializing the array_gen (as this will be very slow if we have to do that process for each iteration)
    % only re-create array files if specified to do so, OR if they have not yet been created (and saved as a model file)
    if option_regenerate || ~exist(sys_filename, 'file')
        
        plot_potential_and_simulation;
        
        %pendulum_control_lmi;
        pendulum_init;
        
        
        % todo: x_init is set in pendulum_init, which is called by this file later, have to set at that call
        iterations_max = length(x_init); % max number of runs
        %iterations_max = 5;

        %array_init; % need to call this before calling array_gen for some settings, e.g., failures that depend on the grid frequency
        %array_gen; % should be ok to call this before array_init as all the parameters in array_gen are symbolic and are defined by the array_init call prior to the first simulation call
    end
    
    for Nf = 1
        %IDfail = [N-(Nf-1):N]; % fail panels with highest indices

        %if option_messages
        %    ['N=', num2str(N), ' F=', num2str(Nf), 'IDs=', strrep(num2str(IDfail),'  ','_'), ' starting at ', datestr(now, formatOut)]
        %end
        
        if option_parallel
            % see: http://www.mathworks.com/help/distcomp/addattachedfiles.html
            apool.addAttachedFiles([sysname, '.slx']);

            for si = 1 : iterations_max
                simout(Ni,Nfi,si).iteration = si;
            end
        end

        % if we have random parameter generation for the different
        % panels, etc, we should batch over a number of runs in a Monte Carlo
        % fashion to get a sensitivity analysis versus the parameter variations
        %parfor si = 1 : iterations_max
        for si = 1 : iteration_step : iterations_max
            % update user on status
            if option_messages
                %['N=', num2str(N), ' F=', num2str(Nf), 'FIDs=', strrep(num2str(IDfail),'  ','_'), 
                ['iteration ', num2str(si), ' starting at ', datestr(now, formatOut)]
            end

            seed = si * 123456; % seed used for various stochastic processes (arrivals, processing rates, etc.)
            rng('default');
            %rng(seed); % set random number generator seed for Matlab functions
            
            % set initial condition
            % TODO: double check order
            %x0 = [ x_init(si); v_init(si); theta_init(si); omega_init(si)];
            x0 = [ x_init(si); theta_init(si); v_init(si); omega_init(si)];
            
            % trying this way to see if just modifying param wouldn't
            % require recompile, but it did, strange
            %set_param([sysname '/init'],'Value',['[',num2str(x0(1)),';',num2str(x0(2)),';',num2str(x0(3)),';',num2str(x0(4)),']']);
            
            simout(Ni,Nfi,si).N = N;
            simout(Ni,Nfi,si).Nf = Nf;
            simout(Ni,Nfi,si).iteration = si;
            simout(Ni,Nfi,si).time_start = toc(time_simstart);
            simout(Ni,Nfi,si).x_init = x_init(si);
            simout(Ni,Nfi,si).x_init = v_init(si);
            simout(Ni,Nfi,si).x_init = theta_init(si);
            simout(Ni,Nfi,si).x_init = omega_init(si);
            simout(Ni,Nfi,si).x0 = x0;
            

            % reinitalize parameters with new N
            %clear TswitchArray;
            %clear agent;
            %array_init;

            % todo next: sys needs to be the pointer to the model object
            %se_randomizeseeds(sys,'Mode','All','GlobalSeed',seed); % set random seeds for Simulink blocks

            % good one: Tgrid+0.011023
            %tfail = Tstartup + Tgrid * (1 + rand(1,1)); % TODO: make a vector, currently only supports one failure (or all at same time)
            %tfail = Tstartup + Tgrid * (1.25);
            
            %simout(Ni,Nfi,si).tfail = tfail; % save failure time
            
            % run simulation
            simout(Ni,Nfi,si).result = sim(sysname, 'StopTime', 'Tmax',  'SimulationMode','normal');
            % run simulation with acceleration
            %simout(Ni,Nfi,si).result = sim(sysname, 'StopTime', 'Tmax', 'SimulationMode','accelerator');
            % run simulation with rapid acceleration
            %simout(Ni,Nfi,si).result = sim(sysname, 'StopTime', 'Tmax', 'SimulationMode', 'rapid');
            %'SimCompilerOptimization', 'on'
            
            % copy local parameters
            %simout(Ni,Nfi,si).vac = simout(Ni,Nfi,si).result.find('ScopeDataSeries');
            
            %simout(Ni,Nfi,si).vdc = simout(Ni,Nfi,si).result.find('ScopeDataSwitching');
            
            %simout(Ni,Nfi,si).vac_tws = simout(Ni,Nfi,si).result.find('VoltageSeriesSave');
            %simout(Ni,Nfi,si).thd = simout(Ni,Nfi,si).result.find('simout_thd');

            % get THD values above the threshold
            %thd_times = simout(Ni,Nfi,si).result.find('simout_thd').Time >= Tstartup+Tgrid; % only get times later than 1 period and the startup time (otherwise will be highly distorted)
            %thd_data = simout(Ni,Nfi,si).result.find('simout_thd').Data;
            %thd_vals = thd_data(find(thd_times == 1));
            %thd_vals(Ni,:) = thd_data(find(thd_data >= thd_threshold));
            %thd_vals = thd_data(find(thd_data >= thd_threshold)); % try for parfor
            %thd_mean(Ni,Nfi,si) = mean(thd_vals);
            %thd_mean(Ni,si) = mean(thd_vals); % parfor
            %thd_std(Ni,Nfi,si) = std(thd_vals);
            %thd_std(Ni,si) = std(thd_vals); % parfor
            
            simout(Ni,Nfi,si).rtreach_safe = rtreach(20, x_init(si), v_init(si), theta_init(si), omega_init(si)); % todo: change runtime part; order is correct, x, v, theta, omega

            simout(Ni,Nfi,si).time_stop = toc(time_simstart);
            simout(Ni,Nfi,si).runtime = simout(Ni,Nfi,si).time_stop - simout(Ni,Nfi,si).time_start;

            % update user on status
            if option_messages
                %['N=', num2str(N), ' F=', num2str(Nf), 'FIDs=', strrep(num2str(IDfail),'  ','_')
                [' iteration ', num2str(si), ' done at ', datestr(now, formatOut), ' in ', num2str(simout(Ni,Nfi,si).runtime), ' sec']
            end
        end
        Nfi = Nfi + 1;
    end
    
    % save primary data during simulation in case simulator crashes
    %save([path_output_data, 'simout', 'N', num2str(N), 'F', num2str(Nf), 'FIDs=', strrep(num2str(IDfail),'  ','_'), datestr(now, formatOut), '.mat'],'simout');
    save([path_output_data, 'simout', '_si=', num2str(si), datestr(now, formatOut), '.mat'],'simout');
    
    
    %save([path_output_data, 'thd_mean', 'N', num2str(N), 'F', num2str(Nf), 'FIDs=', strrep(num2str(IDfail),'  ','_'), datestr(now, formatOut), '.mat'],'thd_mean');
    
    Ni = Ni + 1;
end

Nfi_max = Nfi - 1;

Ni = 1;
Nfi = 1;


figure;
hold on;
% must call plot3 first, else cannot plot into the 2-d figure
for si = 1 : iterations_max
    %plot3(simout(Ni,Nfi,si).result.find('PendulumScopeData').signals(idx_x).values, simout(Ni,Nfi,si).result.find('PendulumScopeData').signals(idx_v).values, simout(Ni,Nfi,si).result.find('PendulumScopeData').time);
    
    if simout(Ni,Nfi,si).rtreach_safe
        %'safe'
        scatter( simout(Ni,Nfi,si).x0(idx_x), simout(Ni,Nfi,si).x0(idx_v), 100, 'go');
    else
        scatter( simout(Ni,Nfi,si).x0(idx_x), simout(Ni,Nfi,si).x0(idx_v), 100, 'rx');
    end
end

%plot(Sxbound1(idx_x:idx_x,:),Sxbound1(idx_v:idx_v,:),'b*');
%plot(lambda.*Sxbound1(idx_x:idx_x,:),lambda.*Sxbound1(idx_v:idx_v,:),'m*');
%plot_potential;
title('Stabilizable Regions for x and \dot{x}');
%legend('Safety', 'Baseline', 'Experimental');
xlabel('x (m)');
ylabel('\dot{x} (m/s)');
axis tight;





figure;
hold on;
% must call plot3 first, else cannot plot into the 2-d figure
for si = 1 : iterations_max
    plot3( radtodeg(simout(Ni,Nfi,si).result.find('PendulumScopeData').signals(idx_theta).values), radtodeg(simout(Ni,Nfi,si).result.find('PendulumScopeData').signals(idx_omega).values), simout(Ni,Nfi,si).result.find('PendulumScopeData').time);
    
    if simout(Ni,Nfi,si).rtreach_safe
        scatter( radtodeg(simout(Ni,Nfi,si).x0(idx_theta)), radtodeg(simout(Ni,Nfi,si).x0(idx_omega)), 100, 'go');
    else
        scatter( radtodeg(simout(Ni,Nfi,si).x0(idx_theta)), radtodeg(simout(Ni,Nfi,si).x0(idx_omega)), 100, 'rx');
    end
end

plot( radtodeg(Sxbound2(idx_theta:idx_theta,:)), radtodeg(Sxbound2(idx_omega:idx_omega,:)),'g*');
plot(lambda.*radtodeg(Sxbound2(idx_theta:idx_theta,:)),lambda.*radtodeg(Sxbound2(idx_omega:idx_omega,:)),'m*');
%plot_potential_angle;
title('Stabilizable Regions for \theta and \dot{\theta}');
%legend('Safety', 'Baseline', 'Experimental');
xlabel('\theta (deg)');
ylabel('\dot{\theta} (deg/s)');












totalTime = toc(time_simstart) % save total simulation time

if option_parallel
    %matlabpool close;
    if ~isempty(gcp)
        delete(gcp);
    end
end

% save entire workspace (probably large)
saveFile = datestr(now, formatOut);
if option_messages
    ['finished simulation at ', saveFile]
    ['it started at ', startTime]
end
saveFile = [path_output_data, 'out-', saveFile, '.mat'];
save(saveFile); % save workspace








