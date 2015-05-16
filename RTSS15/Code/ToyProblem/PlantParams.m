%toy problem

h = 1/100;
% A = [zeros(2,4);1 0 0 0;0 1 0 0];
% B = [1 0;0 1;zeros(2,2)];
B = [-.1 0;0 -1;zeros(2,2)];
A = [zeros(2,4);-1 0 0 0;0 -1 0 0];
C = eye(4);
D = zeros(4,2);
sys = ss(A,B,C,D);
R = 15;

sys_d = c2d(sys,h);
close all
a = 0;
colors = {'k','m', 'b'};
delays = [1 2 8]*h/(4);
clear del err track_err est_error
for i = [1,3]
    t = delays(i);
    a = i;% a+1;
    del(a) = t;
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
