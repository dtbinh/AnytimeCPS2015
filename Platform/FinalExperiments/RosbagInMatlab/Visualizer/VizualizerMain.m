%
folders{1} = '/Users/mlab/Downloads/CSV_Files_05_05_Square/2015-05-05-16-08-13_feat50';
folders{2} = '/Users/mlab/Downloads/CSV_Files_05_05_Square/2015-05-05-16-06-04_feat100';
folders{3} = '/Users/mlab/Downloads/CSV_Files_05_05_Square/2015-05-05-15-59-43_feat200';
folders{4} = '/Users/mlab/Downloads/CSV_Files_05_05_Square/2015-05-05-16-24-05_switchin';
mats = {'square05feat50', 'square05feat100', 'square05feat200', 'square05Switchin'};



plotall = 0;

for f=1:length(folders)
    foldername = folders{f};
    if exist(mats{f},'file')
        disp(['Loading ',mats{f}])
        load(mats{f});
    else
        disp(['loading files from ',foldername])
        % odometry at 20Hz from Vicon
        % 1st column is timestamp always
        odom_drop = importfile_odom_drop([foldername,'/_slash_quadcloud2_slash_odom_drop.csv']);
        % odometry at 100 Hz
        odom = importfile_odom([foldername,'/_slash_quadcloud2_slash_odom.csv']);
        % commanded position from trajetory generator
        pos_cmd = importfile_position_cmd([foldername,'/_slash_quadcloud2_slash_position_cmd.csv']);
        % generated trpy command
        trpy_cmd = importfile_trpy_cmd([foldername,'/_slash_quadcloud2_slash_trpy_cmd.csv']);
        
        %%
        disp('Visualizing ...')
        % actual pos
        figure(1);
        % x,y,z
        plot3(odom_drop(:,12),odom_drop(:,13),odom_drop(:,14),'.b');xlabel('x');ylabel('y');zlabel('z');
        hold on;grid on;
        % x,y,z
        plot3(pos_cmd(:,9),pos_cmd(:,10),pos_cmd(:,11),'.r');xlabel('x');ylabel('y');zlabel('z');
        legend('position','commanded traj');
        
        %manually size, dummy vars
        odorig = odom_drop;
        poscmdorig = pos_cmd;
        trpyorig = trpy_cmd;
        
        % Find shortest signal
        [ss,ssix] = min([size(odom_drop,1), size(pos_cmd,1), size(trpy_cmd,1)]);
        switch ssix
            case 1
                initial_time = odom_drop(1,1);
                a = find(pos_cmd(:,1) <= initial_time);
                if isempty(a)
                    a = find(pos_cmd(:,1) >= initial_time); aix = a(1);
                else
                    aix = a(end);
                end
                pos_cmd = pos_cmd(aix:end,:);
                %
                b = find(trpy_cmd(:,1) <= initial_time);
                if isempty(b)
                    b = find(trpy_cmd(:,1) >= initial_time); bix = b(1);
                else
                    bix = b(end);
                end
                trpy_cmd = trpy_cmd(bix:end,:);
                
            case 2
                initial_time = pos_cmd(1,1);
                a = find(odom_drop(:,1) <= initial_time);
                if isempty(a)
                    a = find(odom_drop(:,1) >= initial_time); aix = a(1);
                else
                    aix = a(end);
                end
                odom_drop = odom_drop(aix:end,:);
                %
                b = find(trpy_cmd(:,1) <= initial_time);
                if isempty(b)
                    b = find(trpy_cmd(:,1) >= initial_time); bix = b(1);
                else
                    bix = b(end);
                end
                trpy_cmd = trpy_cmd(bix:end,:);
                
            case 3
                initial_time = trpy_cmd(1,1);
                a = find(odom_drop(:,1) <= initial_time);
                if isempty(a)
                    a = find(odom_drop(:,1) >= initial_time); aix = a(1);
                else
                    aix = a(end);
                end
                odom_drop = odom_drop(aix:end,:);
                %
                b = find(pos_cmd(:,1) <= initial_time);
                if isempty(b)
                    b = find(pos_cmd(:,1) >= initial_time); bix = b(1);
                else
                    bix = b(end);
                end
                pos_cmd = pos_cmd(bix:end,:);
        end
        size(odom_drop)
        size(trpy_cmd)
        size(pos_cmd)
        save(mats{f}, 'odom_drop','trpy_cmd','pos_cmd');
    end
    
    % commanded and actual positions
    if (plotall)
        figure
        subplot(311)
        plot(pos_cmd(:,9)); hold all;plot(odom_drop(:,12));grid on;
        ylabel('x');
        subplot(312)
        plot(pos_cmd(:,10)); hold all;plot(odom_drop(:,13));grid on;
        ylabel('y');
        subplot(313)
        plot(pos_cmd(:,11)); hold all;plot(odom_drop(:,14));grid on;
        ylabel('z');
        legend('cmd','actual');
    end
    
    % errors in position
    
    err_pos_x = abs(pos_cmd(:,9)-odom_drop(:,12));
    err_pos_y = abs(pos_cmd(:,10)-odom_drop(:,13));
    err_pos_z = abs(pos_cmd(:,11)-odom_drop(:,14));
    
    % velocity from vicon 20hz
    vel_x = odom_drop(:,59); %vicon
    vel_y = odom_drop(:,60);
    vel_z = odom_drop(:,61);
    
    % error in velocities (commanded-vicon)
    err_vel_x = abs(pos_cmd(:,13)-vel_x);
    err_vel_y = abs(pos_cmd(:,14)-vel_y);
    err_vel_z = abs(pos_cmd(:,15)-vel_z);
    
    % commanded acceleration
    acc_x = odom_drop(:,63);
    acc_y = odom_drop(:,64);
    acc_z = odom_drop(:,65);
    
    % vector of inputs (pitch, roll, thrust)
    u_vec = [trpy_cmd(:,10) trpy_cmd(:,9) trpy_cmd(:,8)-4.905]; %P,R,T-mg
    Mode = trpy_cmd(:,24); %mode
    
    if plotall
        figure;
        plot(err_pos_x,'b');hold on;grid on;
        plot(err_pos_y,'g');hold on;
        plot(err_pos_z,'r');hold on;
        legend('err x', 'err y','err z');
    end
    
    %% opt cost tracking
    Q = diag([10 10 10 .1 .1 .1]);
    R = diag([5 5 1]);
    
    comp_cost = 0;
    cost_pos = zeros(numel(err_pos_x),1);
    cost_sys = zeros(numel(err_pos_x),1);
    err_vec = [err_pos_x err_pos_y err_pos_z err_vel_x err_vel_y err_vel_z];
    for i = 1:numel(err_pos_x)-1
        cost_pos(i) = [err_pos_x(i) err_pos_y(i) err_pos_z(i)]*Q(1:3,1:3)*[err_pos_x(i) err_pos_y(i) err_pos_z(i)]';
        cost_sys(i) = err_vec(i,:)*Q*err_vec(i,:)' + u_vec(i,:)*R*u_vec(i,:)';
    end
    if plotall
        figure;
        hold on;
        plot(cost_sys);grid on;
        title('quadratic cost of pos track');
    end
    %% err stats
    clc;
    'mean abs error [x y z]'
    [mean(err_pos_x) mean(err_pos_y) mean(err_pos_z)]
    '2-norm of abs err/no of samples [x y z]'
    [norm(err_pos_x) norm(err_pos_y) norm(err_pos_z)]./numel(err_pos_x)
    'RMS err [x y z]'
    [rms(err_pos_x) rms(err_pos_y) rms(err_pos_z)]
    'max abs err [x y z]'
    [max(err_pos_x) max(err_pos_y) max(err_pos_z)]
    'mean pos track cost'
    mean(cost_pos)
    'mean and max cost'
    [mean(cost_sys) max(cost_sys)]
    
end


