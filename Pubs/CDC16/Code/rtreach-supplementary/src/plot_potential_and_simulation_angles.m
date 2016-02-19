% Stanley Bak
% 4-28-2014
% Plot where the potential is < 1, and where the input is out of bounds

% step size in the plot
%step = 0.025;
%step = 0.05;
%step = 0.025;

% step = 0.02; % original submission
%step = 0.005; % camera ready probably too fine
step = 0.005;

%theta_step = 0.01; % original submission
%theta_step = 0.001; % camera ready probably too fine
theta_step = 0.005;

tic

% state bounds
%(x < -1 || x > 1 ...
%       || vel < -1 || vel > 1 ...
%       || theta < degtorad(-15) || theta > degtorad(15))

% potential matrix, we will plot when x^t * P * x  < 1
P = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];

% gain matrix from lmi optimization
K = [  0.4072 7.2373  18.6269   3.6725  ];

% bad states that time out
bad_states(1,:) = [1.1000; 0; 0; 0];
bad_states(2,:) = [1.1000; 0; 0; 0];

%THETA = 0.025;
%OMEGA = -0.1;
%THETA = 0.19;
%OMEGA = 0.18;
%THETA = 0;
%OMEGA = 0;
x = 0;
y = 0;

figure;
clf
hold on

clear init_to_try;
init_to_try(1,:) = [0, 0, 0, 0];
itry = 1; % overwrite first entry

v_min = degtorad(-17.5); % theta
v_max = degtorad(17.5);
x_min = degtorad(-165); % omega
x_max = degtorad(165);

for THETA=v_min:theta_step:v_max
  for OMEGA=x_min:step:x_max
    state_swapped = [x ; THETA ; y ; OMEGA]; % notice swapping of column 2 and 3
    
    potential = state_swapped.' * P * state_swapped;
    
    %color = 'b.';
    
    if (potential < 1)
        color = 'co';
        plot(THETA, OMEGA, color)
    end
        
    
   
    %%%%%%%%%% check simulation
    
    if (potential >= 1)
        state = [x ; y ; THETA ; OMEGA];
        
        %state
        
        if sum(ismember(bad_states, state', 'rows')) > 0
            'skipping bad state'
            continue;
        end
        
        if rtreach(20, state(1), state(2), state(3), state(4)) % this is the right order, rtreach(runtime, x, v, theta, omega)
            plot(THETA, OMEGA, 'g*')
        elseif (checkSimulation(state, 2))
            plot(THETA, OMEGA, 'y+')
            init_to_try(itry,:) = state_swapped'; % use swapped state
            itry = itry + 1;
        else
            plot(THETA, OMEGA, 'rx')
        end
    end
    
    
  end
  
  drawnow  

end

hold off

%title('Potential < 1 (yellow dots); -4.95 < u < 4.95 (green circles)')
%xlabel('Position, p (m)')
%ylabel('Velocity, v (m/s)')
xlabel('Angle, \theta (rad)')
ylabel('Angular Velocity, \omega (rad/s)')
axis tight;

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