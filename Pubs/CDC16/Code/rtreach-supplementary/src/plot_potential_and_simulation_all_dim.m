% Stanley Bak
% 4-28-2014
% Plot where the potential is < 1, and where the input is out of bounds

% step size in the plot
%step = 0.025;
%step = 0.05;
step = 0.025;
%step = 0.01;

tic

% state bounds
%(x < -1 || x > 1 ...
%       || vel < -1 || vel > 1 ...
%       || theta < degtorad(-15) || theta > degtorad(15))

%num_samples = 5;
%num_samples = 10; % 1 min
%num_samples = 30; % 50 min
num_samples = 14;

runtimes = [2, 5, 10, 20, 30, 40, 50, 75, 100, 200, 500, 1000];

iter = 1;

%for num_samples = 11 : 20
for rt = runtimes

    bound_x_min = -1.25;
    bound_x_max = 1.25;
    x_step = (bound_x_max - bound_x_min) / num_samples;
    bound_v_min = -1.2;
    bound_v_max = 1.2;
    v_step = (bound_v_max - bound_v_min) / num_samples;
    bound_theta_min = degtorad(-20);
    bound_theta_max = degtorad(20);
    theta_step = (bound_theta_max - bound_theta_min) / num_samples;
    bound_omega_min = degtorad(-30);
    bound_omega_max = degtorad(30);
    omega_step = (bound_omega_max - bound_omega_min) / num_samples;

    % potential matrix, we will plot when x^t * P * x  < 1
    P = [
        1.0520    1.2082    0.2580    0.1988 ;
        1.2082   33.9334    4.6631    4.0269 ;
        0.2580    4.6631    2.2108    1.0090 ;
        0.1988    4.0269    1.0090    0.8424 ];

    % gain matrix from lmi optimization
    K = [  0.4072 7.2373  18.6269   3.6725  ];

    % bad states that time out
    %bad_states(1,:) = [1.1000; 0; 0; 0];
    %bad_states(2,:) = [1.1000; 0; 0; 0];

    %figure;
    %clf;
    %hold on;

    clear init_to_try;
    init_to_try(1,:) = [0, 0, 0, 0];
    itry = 1; % overwrite first entry

    option_draw = 0;

    count_ellipsoid = 0;
    count_unsafe = 0;
    count_rtreach_safe = 0;
    count_simulation_safe = 0;

    counted = 0; % flag to check if state counted yet or not

    for omega_i = bound_omega_min : omega_step : bound_omega_max
        for theta_i = bound_theta_min : theta_step : bound_theta_max

            %figure;
            %hold on;

            if option_draw
                clf;
                hold on;
                xlim([bound_x_min, bound_x_max]);
                ylim([bound_v_min, bound_v_max]);
                title(['\theta = ', num2str(theta_i), ' \omega = ', num2str(omega_i)])
                xlabel('Position')
                ylabel('Velocity')
            end
            for y = bound_v_min : v_step : bound_v_max
                for x = bound_x_min : x_step : bound_x_max
                    counted = 0;

                    state_swapped = [x ; theta_i ; y ; omega_i]; % notice swapping of column 2 and 3
                    %state_swapped

                    potential = state_swapped.' * P * state_swapped;

                    %color = 'b.';

                    if (potential < 1)
                        if ~counted
                            count_ellipsoid = count_ellipsoid + 1;
                            counted = 1;
                        end

                        if option_draw
                            color = 'b.';
                            plot(x, y, color)
                        end
                    end

                    %%%%%%%%%% check simulation

                    if (potential >= 1)
                        state = [x ; y ; theta_i ; omega_i];

                        %state

                        %if sum(ismember(bad_states, state', 'rows')) > 0
                        %    'skipping bad state'
                        %    continue;
                        %end

                        if rtreach(rt, state(1), state(2), state(3), state(4)) % this is the right order, rtreach(runtime, x, v, theta, omega)
                            if ~counted
                                count_rtreach_safe = count_rtreach_safe + 1;
                                counted = 1;
                            end

                            if option_draw
                                plot(x, y, 'gx')
                            end
                        elseif (checkSimulation(state, 2))
                            if ~counted
                                count_simulation_safe = count_simulation_safe + 1;
                                counted = 1;
                            end


                            if option_draw
                                plot(x, y, 'y*')
                            end
                            init_to_try(itry,:) = state_swapped'; % use swapped state
                            itry = itry + 1;
                        else
                            if ~counted
                                count_unsafe = count_unsafe + 1;
                                counted = 1;
                            end

                            if option_draw
                                plot(x, y, 'r.')
                            end
                        end
                    end
                end
                if option_draw
                    drawnow
                end
            end
            toc
        end
        'slice done'
        toc
    end

    if option_draw
        hold off

        %title('Potential < 1 (yellow dots); -4.95 < u < 4.95 (green circles)')
        xlabel('Position')
        ylabel('Velocity')
        axis tight;
    end

    idx_x = 1;
    idx_v = 3;
    idx_theta = 2;
    idx_omega = 4;

    toc


    init_to_try = init_to_try';
    x_init = [init_to_try(idx_x:idx_x,:)];
    v_init = [init_to_try(idx_v:idx_v,:)];
    theta_init = [init_to_try(idx_theta:idx_theta,:)]; % keep rad
    omega_init = [init_to_try(idx_omega:idx_omega,:)]; % keep rad

    ['Number of initial conditions: ', num2str(length(init_to_try))]

    (num_samples+1)^4
    count_ellipsoid
    count_unsafe
    count_rtreach_safe
    count_simulation_safe

    'checked points'
    count_ellipsoid + count_unsafe + count_rtreach_safe + count_simulation_safe

    'percentage increase'
    improvement(iter) = (count_rtreach_safe + count_ellipsoid) / count_ellipsoid
    
    
    c_ell(iter) = count_ellipsoid;
    c_rtr(iter) = count_rtreach_safe;
    c_conv(iter) = count_simulation_safe;
    c_unsafe(iter) = count_unsafe;
    
    
    iter = iter + 1
 
end

% 1 to 10
%improvement = NaN    1.0000    1.0909    2.1163    2.5204    2.6632    2.6639    2.5417    2.3277    2.3715


%improvement =
%  Columns 1 through 11
%         0         0         0         0         0         0         0         0         0         0    2.2462
%  Columns 12 through 20
%
%    2.3352    2.1956    2.2679    2.3252    2.3154    2.2182    2.2899    2.3351    2.3724




% runtimes:
% runtimes = [2,        5,        10,       20,       30,       40,       50,       75,      100,       200,    500,    1000];
%             2.2009    2.1978    2.2000    2.3498    2.3497    2.3756    2.3844    2.3898
%             2.2009    2.1978    2.2000    2.3498    2.3497    2.3756    2.3844    2.3898    2.4029    2.4163
%2.2009    2.1978    2.2000    2.3498    2.3497    2.3756    2.3844    2.3898    2.4029    2.4163
%
%improvement =
%2.2009    2.1978    2.2000    2.3498    2.3497    2.3756    2.3844    2.3898    2.4029    2.4163