filepath = '~/bag_files/bag_files/2016-05-09/2016-05-09-15-13-27.bag';
bag = rosbag(filepath);
svo_odom = select(bag,'Topic','/svo/odom');
msgs  = readMessages(svo_odom);
%Pose_position = [msgs{1}.Pose.Pose.Position.X msgs{1}.Pose.Pose.Position. Y 
ts = timeseries(svo_odom,'Pose.Pose.Position.X','Pose.Pose.Position.Y','Pose.Pose.Position.Y');
size(ts.data);

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

%plot3
figure;
plot3(Vic_Pose_Pos.Data(:,1),Vic_Pose_Pos.Data(:,2),Vic_Pose_Pos.Data(:,3));
hold all;
grid on;
plot3(Vis_Pose_Pos.Data(:,1),Vis_Pose_Pos.Data(:,2),Vis_Pose_Pos.Data(:,3));

%error
err_x = Vic_Pose_Pos.Data(:,1) - Vis_Pose_Pos.Data(:,1);
err_y = Vic_Pose_Pos.Data(:,2) - Vis_Pose_Pos.Data(:,2);
err_z = Vic_Pose_Pos.Data(:,3) - Vis_Pose_Pos.Data(:,3);

[Vis_yaw,Vis_pitch,Vis_roll] = quat2angle(Vis_Pose_Ori.data);
[Vic_yaw,Vic_pitch,Vic_roll] = quat2angle(Vic_Pose_Ori.data);

err_yaw = Vis_yaw-Vic_yaw;
err_pitch = Vis_pitch-Vic_pitch;
err_roll = Vis_roll-Vic_roll;