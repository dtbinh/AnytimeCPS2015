%toy problem

h = 1/20;
A = [zeros(2,4);1 0 0 0;0 1 0 0];
B = [1 0;0 1;zeros(2,2)];
C = eye(4);
D = zeros(4,2);
sys = ss(A,B,C,D);

sys_d = c2d(sys,h);
close all
a = 0;
colors = {'k','b','m'};
delays = [1 2 8]*h/(4*5);
clear del err track_err est_error
for t = delays%[1 2 8]/5
    a = a+1;
    del(a) = t;%(t*h/4);
    if(del(a)~=0)
        err(a) = (1/del(a))*(1/1000);
%         err(a) = errors(a);
    else
        err(a) = 0.001;
    end
    delay = del(a);
    est_error = err(a);
    sim('pointmassim.slx');
    
    
    track_err(a) = sum(abs(plant.signals(3).values(:,1)-plant.signals(3).values(:,2)) ...
        +abs(plant.signals(4).values(:,1)-plant.signals(4).values(:,2)));
    
    figure(1);    
    hold on;
    R = 15;
%     y = decimate(plant.signals(4).values(:,1),R);
%     y = decimate(y,R);
%     ts = plant.time(1:2*R:end);
    y = downsample(plant.signals(4).values(:,1),R);
    ts = downsample(plant.time,R);
    plot(ts,y,colors{a})
end
legend(num2str(delays(1)),num2str(delays(2)),num2str(delays(3)));
hold on;
ref = plant.signals(3).values(:,2);
ref = downsample(ref,R);
plot(ts,ref, 'k', 'LineWidth', 3);

% figure;%semilogy(del,track_err,'so');grid on;
% semilogy(del,track_err,'--gs',...
%     'LineWidth',2,...
%     'MarkerSize',10,...
%     'MarkerEdgeColor','b',...
%     'MarkerFaceColor',[0.5,0.5,0.5]);grid on;
