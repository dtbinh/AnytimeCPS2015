%run tmuxinator start ErrorComp for running shit and logging data after bag
%file play
close all;clc;
filepath = '~/bag_files/bag_files/processed/2017/profiling/run2_550fts.bag';
bag = rosbag(filepath);

%offset for end if needed
off_end = 0; %2016-05-12/run2/, use 30 or above, 50 works for run3 as well


%svo_odom = select(bag,'Topic','/svo/odom');
%msgs  = readMessages(svo_odom);
%Pose_position = [msgs{1}.Pose.Pose.Position.X msgs{1}.Pose.Pose.Position. Y
%ts = timeseries(svo_odom,'Pose.Pose.Position.X','Pose.Pose.Position.Y','Pose.Pose.Position.Y');
%size(ts.data);

%get vicon pose
Vicon_Pose = select(bag,'Topic','/vo_test/Vicon_Pose');
Vic_Pose_Pos = timeseries(Vicon_Pose,'Pose.Position.X','Pose.Position.Y','Pose.Position.Z');
Vic_Pose_Ori = timeseries(Vicon_Pose,'Pose.Orientation.W','Pose.Orientation.X', ...
    'Pose.Orientation.Y','Pose.Orientation.Z');
%get SVO pose
Vision_Pose = select(bag,'Topic','/vo_test/Vision_Pose');
Vis_Pose_Pos = timeseries(Vision_Pose,'Pose.Position.X','Pose.Position.Y','Pose.Position.Z');
Vis_Pose_Ori = timeseries(Vision_Pose,'Pose.Orientation.W','Pose.Orientation.X', ...
    'Pose.Orientation.Y','Pose.Orientation.Z');

%% plot3
if(0)
    figure;
    axis([-2 2 -2 2 0 3]);
    
    for i = 1:size(Vic_Pose_Pos.Data,1)-off_end
        axis([-2 2 -2 2 0 3]);
        plot3(Vic_Pose_Pos.Data(i,1),Vic_Pose_Pos.Data(i,2), ...
            Vic_Pose_Pos.Data(i,3),'r*');
        %hold all;
        hold on;
        grid on;
        plot3(Vis_Pose_Pos.Data(i,1),Vis_Pose_Pos.Data(i,2), ...
            Vis_Pose_Pos.Data(i,3),'bo');
        legend('Vicon','Vision');
        pause(1/20);
        hold on;
    end
end
%
% plot3(Vic_Pose_Pos.Data(1:end-off_end,1),Vic_Pose_Pos.Data(1:end-off_end,2), ...
%     Vic_Pose_Pos.Data(1:end-off_end,3));
% hold all;
% grid on;
% plot3(Vis_Pose_Pos.Data(1:end-off_end,1),Vis_Pose_Pos.Data(1:end-off_end,2), ...
%     Vis_Pose_Pos.Data(1:end-off_end,3));
% legend('Vicon','Vision');
%%
%error
err_x = Vic_Pose_Pos.Data(1:end-off_end,1) - Vis_Pose_Pos.Data(1:end-off_end,1);
err_y = Vic_Pose_Pos.Data(1:end-off_end,2) - Vis_Pose_Pos.Data(1:end-off_end,2);
err_z = Vic_Pose_Pos.Data(1:end-off_end,3) - Vis_Pose_Pos.Data(1:end-off_end,3);

[Vis_yaw,Vis_pitch,Vis_roll] = quat2angle(Vis_Pose_Ori.data(1:end-off_end,:));
[Vic_yaw,Vic_pitch,Vic_roll] = quat2angle(Vic_Pose_Ori.data(1:end-off_end,:));

err_yaw = Vis_yaw-Vic_yaw;
err_pitch = Vis_pitch-Vic_pitch;
err_roll = wrapTo2Pi(Vis_roll)-wrapTo2Pi(Vic_roll);

'Number of data points'
numel(err_yaw)
'stats'
[mean(err_x) std(err_x)]
[mean(err_y) std(err_y)]
[mean(err_z) std(err_z)]

temp_errs = [err_x err_y err_z err_yaw err_pitch err_roll];
Data_rec = [Data_rec;temp_errs];
%% plot hists
if(1)
    figure;
    subplot(321)
    histogram(err_yaw-mean(err_yaw))
    %title('yaw')
    xlabel('yaw err')
    
    subplot(323)
    histogram(err_pitch-mean(err_pitch))
    xlabel('pitch err')
    
    subplot(325)
    histogram(err_roll-mean(err_roll))
    xlabel('roll err')
    
    subplot(322)
    histogram(err_x-mean(err_x))
    xlabel('x err')
    
    subplot(324)
    histogram(err_y-mean(err_y))
    xlabel('y err')
    
    subplot(326)
    histogram(err_z-mean(err_z))
    xlabel('z err')
end
%% re load stuff
err_x = Data_rec(:,1);
err_y = Data_rec(:,2);
err_z = Data_rec(:,3);
err_yaw = Data_rec(:,4);
err_pitch = Data_rec(:,5);
err_roll = Data_rec(:,6);


[h,p,stats] = chi2gof(err_x); %use this to test
figure;
subplot(311);
qqplot(err_x);
subplot(312);
qqplot(err_y);
subplot(313);
qqplot(err_z);

%%
