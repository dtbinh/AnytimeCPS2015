%%
%x='*.bag';
%f = dir(x); %assuming one bag here
foldername = '/Users/mlab/Downloads/CSV_Files_05_05/2015-05-05-15-59-43_feat200';
'loading file ...'
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
'Visualizing ...'
% actual pos
figure;
% x,y,z
plot3(odom_drop(:,12),odom_drop(:,13),odom_drop(:,14),'.b');xlabel('x');ylabel('y');zlabel('z');
hold on;grid on;
% x,y,z
plot3(pos_cmd(:,9),pos_cmd(:,10),pos_cmd(:,11),'.r');xlabel('x');ylabel('y');zlabel('z');
legend('position','commanded traj');


% %synchronize (assuming pos cmd after rest)
% if(size(pos_cmd,1)~=size(odom_drop,1))
%  

%  [~,ix] = min(diffs);	
%  if(size(odom_drop(ix:end,:),1)~=size(pos_cmd,1))
%   temp = odom_drop(ix-(size(odom_drop(ix:end,:),1)-size(pos_cmd,1)) ,:);   
%  else
%   temp = odom_drop(ix:end,:);
%   clear odom_drop;
%   odom_drop = temp;
% 
%  end
% 
% 
% end

%manually size
N = 1000;
odom_drop = odom_drop(1:N,:);
pos_cmd = pos_cmd(1:N,:);
trpy_cmd = trpy_cmd(1:N,:);

% errs
err_pos_x = abs(pos_cmd(:,9)-odom_drop(:,12));
err_pos_y = abs(pos_cmd(:,10)-odom_drop(:,13));
err_pos_z = abs(pos_cmd(:,11)-odom_drop(:,14));

vel_x = odom_drop(:,59); %vicon
vel_y = odom_drop(:,60);
vel_z = odom_drop(:,61);

err_vel_x = abs(pos_cmd(:,13)-vel_x);
err_vel_y = abs(pos_cmd(:,14)-vel_y);
err_vel_z = abs(pos_cmd(:,15)-vel_z);

acc_r = odom_drop(:,63);
acc_y = odom_drop(:,64);
acc_z = odom_drop(:,65);

u_vec = [trpy_cmd(:,10) trpy_cmd(:,9) trpy_cmd(:,8)-4.905]; %P,R,T-mg

figure;
plot(err_pos_x,'b');hold on;grid on;
plot(err_pos_y,'g');hold on;
plot(err_pos_z,'r');hold on;
legend('err x', 'err y','err z');

% opt cost tracking 
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
figure;
hold on;
plot(cost_sys);grid on;
title('quadratic cost of pos track');
%% err stats
clc;
'mean abs error [x y z]'
[mean(err_pos_x) mean(err_pos_y) mean(err_pos_z)]
'2-norm err/no of samples [x y z]'
[norm(err_pos_x) norm(err_pos_y) norm(err_pos_z)]./numel(err_pos_x)
'RMS err [x y z]'
[rms(err_pos_x) rms(err_pos_y) rms(err_pos_z)]
'max abs err [x y z]'
[max(err_pos_x) max(err_pos_y) max(err_pos_z)]
'mean pos track cost'
mean(cost_pos)
'mean cost'
mean(cost_sys)




