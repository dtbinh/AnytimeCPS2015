%pendulum_plot_all

idx_position = 1;
idx_velocity = 3;
idx_theta = 2;
idx_velocity_angular = 4;

figure;
hold on;
plot(Sxbound1(1:1,:),Sxbound1(3:3,:),'bo');
plot(Bxbound1(1:1,:),Bxbound1(3:3,:),'g*');
plot(Exbound1(1:1,:),Exbound1(3:3,:),'k+');
plot3(PendulumScopeData.signals(idx_position).values, PendulumScopeData.signals(idx_velocity).values, PendulumScopeData.time);
title('Stabilizable Regions for x and xDot');
legend('Safety', 'Baseline', 'Experimental');
xlabel('x (m)');
ylabel('xDot (m/s)');

figure;
hold on;
plot( radtodeg(Sxbound2(idx_theta:idx_theta,:)), radtodeg(Sxbound2(idx_velocity_angular:idx_velocity_angular,:)),'bo');
plot( radtodeg(Bxbound2(idx_theta:idx_theta,:)), radtodeg(Bxbound2(idx_velocity_angular:idx_velocity_angular,:)),'g*');
plot( radtodeg(Exbound2(idx_theta:idx_theta,:)), radtodeg(Exbound2(idx_velocity_angular:idx_velocity_angular,:)),'k+');
plot3(PendulumScopeData.signals(idx_theta).values, PendulumScopeData.signals(idx_velocity_angular).values, PendulumScopeData.time);
title('Stabilizable Regions for \theta and \theta Dot');
legend('Safety', 'Baseline', 'Experimental');
xlabel('\theta (deg)');
ylabel('\theta Dot (deg/s)');

