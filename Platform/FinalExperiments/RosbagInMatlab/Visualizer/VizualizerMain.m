%%
%x='*.bag';
%f = dir(x); %assuming one bag here
'loading file ...'
odom_drop = importfile_odom_drop('_slash_quadcloud2_slash_odom_drop.csv');
odom = importfile_odom('_slash_quadcloud2_slash_odom.csv');
pos_cmd = importfile_position_cmd('_slash_quadcloud2_slash_position_cmd.csv');

%%
'Visualizing ...'
% actual pos
plot3(odom_drop(:,12),odom_drop(:,13),odom_drop(:,14),'.b');xlabel('x');ylabel('y');zlabel('z');
hold on;grid on;
plot3(pos_cmd(:,9),pos_cmd(:,10),pos_cmd(:,11),'.r');xlabel('x');ylabel('y');zlabel('z');
legend('position','commanded traj');

% errs
err_x = abs(pos_cmd(:,9)-odom_drop(:,12));
err_y = abs(pos_cmd(:,10)-odom_drop(:,13));
err_z = abs(pos_cmd(:,11)-odom_drop(:,14));

figure;
plot(err_x,'b');hold on;grid on;
plot(err_y,'g');hold on;
plot(err_z,'r');hold on;
legend('err x', 'err y','err z');

% opt cost tracking position only
Q = diag([10 10 10 .1 .1 .1]);
cost_pos = zeros(numel(err_x),1);
for i = 1:numel(err_x)
    cost_pos(i) = [err_x(i) err_y(i) err_z(i)]*Q(1:3,1:3)*[err_x(i) err_y(i) err_z(i)]';
    
end
figure;
hold on;
plot(cost_pos);grid on;
title('quadratic cost of pos track');

%% err stats
clc;
'mean abs error [x y z]'
[mean(err_x) mean(err_y) mean(err_z)]
'2-norm err/no of samples [x y z]'
[norm(err_x) norm(err_y) norm(err_z)]./numel(err_x)
'RMS err [x y z]'
[rms(err_x) rms(err_y) rms(err_z)]
'max abs err [x y z]'
[max(err_x) max(err_y) max(err_z)]
'mean pos track cost'
mean(cost_pos)



