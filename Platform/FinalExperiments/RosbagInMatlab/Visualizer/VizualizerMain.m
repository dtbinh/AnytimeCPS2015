%% read
close all;
clear pos_cmd odom_drop goal trpy_cmd
'folder info here'
 folder = '2015-05-10-00-24-27_switching_fast'
%folder = '2015-05-09-23-59-47_mode3'

if(new)
'loading file ...'
odom_drop = importfile_odom_drop([folder,'/_slash_quadcloud2_slash_odom_drop.csv']);
%odom = importfile_odom('2015-05-05-16-06-04_feat100/_slash_quadcloud2_slash_odom.csv');
pos_cmd = importfile_position_cmd([folder,'/_slash_quadcloud2_slash_position_cmd.csv']);
trpy_cmd = importfile_trpy_cmd([folder,'/_slash_quadcloud2_slash_trpy_cmd.csv']);
trigger = importfile_goal([folder,'/_slash_quadcloud2_slash_controllers_manager_slash_circle_tracker_slash_trigger.csv']);
save(['/home/mlab-retro/Documents/Py/2015-05-09/',folder,'/',folder,'.mat'],'pos_cmd','trpy_cmd','trigger','odom_drop');
else
   load(['/home/mlab-retro/Documents/Py/2015-05-09/',folder,'/',folder,'.mat']);
end

circlelen = 400; %slow and med
%circlelen = 280; %fast
%%
'Visualizing ...'
% actual pos
figure;
plot3(odom_drop(:,12),odom_drop(:,13),odom_drop(:,14),'.b');xlabel('x');ylabel('y');zlabel('z');
hold on;grid on;
plot3(pos_cmd(:,9),pos_cmd(:,10),pos_cmd(:,11),'.r');xlabel('x');ylabel('y');zlabel('z');
legend('position','commanded traj');



%manually size, dummy vars
odorig = odom_drop;
poscmdorig = pos_cmd;
trpyorig = trpy_cmd;

size(odorig)
size(poscmdorig)
size(trpyorig)
%% 
 
% [~,ix_od_start] = min(abs(trigger(1)-odorig(1,1)));
% [~,ix_pos_start] = min(abs(trigger(1)-poscmdorig(1,1)));
% [~,ix_trpy_start] = min(abs(trigger(1)-trpyorig(1,1)));
% 
% length_allowed = min([length(odorig(ix_od_start:end,1)),length(poscmdorig(ix_pos_start:end,1)),length(trpyorig(ix_trpy_start:end,1))]);
% 
% ix_od_end = ix_od_start+length_allowed-1;
% ix_pos_end = ix_pos_start+length_allowed-1;
% ix_trpy_end = ix_trpy_start+length_allowed-1;
% 
% odom_drop = odorig(ix_od_start:ix_od_end,:);
% pos_cmd = poscmdorig(ix_pos_start:ix_pos_end,:);
% trpy_cmd = trpyorig(ix_trpy_start:ix_trpy_end,:);

[b,ix] = min([length(odorig(:,1)),length(poscmdorig(:,1)),length(trpyorig(:,1))]);



odom_drop = odorig((1+length(odorig(:,1))-b):end,:);
pos_cmd = poscmdorig((1+length(poscmdorig(:,1))-b):end,:);
trpy_cmd = trpyorig((1+length(trpyorig(:,1))-b):end,:);
[~,ix_trigger] = min(abs(trigger(1,1)-odom_drop(:,1)));

%offset trigger
ix_trigger = ix_trigger + 90;%120;

% commanded and actual positions
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
figure;
alpha = 1;
power_consumption = [0.77;0.86;0.8702;0.95];
plot(Mode);grid on;

figure;
plot(err_pos_x,'b');hold on;grid on;
plot(err_pos_y,'g');hold on;
plot(err_pos_z,'r');hold on;
legend('err x', 'err y','err z');

% opt cost tracking 
Q = diag([10 10 10 .1 .1 .1]);
R = diag([5 5 1]);


cost_pos = zeros(numel(err_pos_x),1);
cost_sys = zeros(numel(err_pos_x),1);
cost_sys_power = cost_sys;
err_vec = [err_pos_x err_pos_y err_pos_z err_vel_x err_vel_y err_vel_z];
for i = 1:numel(err_pos_x)-1
    cost_pos(i) = [err_pos_x(i) err_pos_y(i) err_pos_z(i)]*Q(1:3,1:3)*[err_pos_x(i) err_pos_y(i) err_pos_z(i)]';
    cost_sys(i) = err_vec(i,:)*Q*err_vec(i,:)' + u_vec(i,:)*R*u_vec(i,:)';
    cost_sys_power(i) = cost_sys(i) + alpha*power_consumption'*[Mode(i)==0;Mode(i)==1;Mode(i)==2;Mode(i)==3];
end
figure;
hold on;
plot(cost_sys);grid on;
title('quadratic cost of pos track');
hold all;
plot(Mode);

% err stats
clc;
% 'mean abs error [x y z]'
% [mean(err_pos_x) mean(err_pos_y) mean(err_pos_z)]
% '2-norm err/no of samples [x y z]'
% [norm(err_pos_x) norm(err_pos_y) norm(err_pos_z)]./numel(err_pos_x)
% 'RMS err [x y z]'
% [rms(err_pos_x) rms(err_pos_y) rms(err_pos_z)]
% 'max abs err [x y z]'
% [max(err_pos_x) max(err_pos_y) max(err_pos_z)]
% 'mean pos track cost'
% mean(cost_pos)
'trigger at'
ix_trigger
'mode time spent from trigger onwards to end of circle'
sprintf('Fraction time in Mode 0, Mode 1, Mode 2, Mode 3: %f %f %f %f', ... 
    [sum(Mode(ix_trigger:ix_trigger+circlelen)==0)/(length(ix_trigger:ix_trigger+circlelen)), ...
    sum(Mode(ix_trigger:ix_trigger+circlelen)==1)/(length(ix_trigger:ix_trigger+circlelen)), ... 
    sum(Mode(ix_trigger:ix_trigger+circlelen)==2)/(length(ix_trigger:ix_trigger+circlelen)), ...
    sum(Mode(ix_trigger:ix_trigger+circlelen)==3)/(length(ix_trigger:ix_trigger+circlelen))])
'mean tracking cost and std'
[mean(cost_sys(ix_trigger:ix_trigger+circlelen)) std(cost_sys(ix_trigger:ix_trigger+circlelen))]
'mean system cost and std'
[mean(cost_sys_power(ix_trigger:ix_trigger+circlelen)) std(cost_sys_power(ix_trigger:ix_trigger+circlelen))]
%% save
save(strcat('/home/mlab-retro/Documents/Py/2015-05-08/MatData/',folder,'.mat'),'cost_sys','Mode','odom_drop','pos_cmd','trpy_cmd');


