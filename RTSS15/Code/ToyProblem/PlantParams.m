%toy problem

h = 1/20;
A = [zeros(2,4);1 0 0 0;0 1 0 0];
B = [1 0;0 1;zeros(2,2)];
C = eye(4);
D = zeros(4,2);
sys = ss(A,B,C,D);

sys_d = c2d(sys,h);

a = 0;
for t = 1:5:26
a = a+1;
del(a) = (t*h/4);
err(a) = 0;%(1/del(a))*(1/100);
delay = del(a);
est_error = err(a);
sim('pointmassim.slx');


track_err(a) = sum(abs(plant.signals(3).values(:,1)-plant.signals(3).values(:,2)) ... 
    +abs(plant.signals(4).values(:,1)-plant.signals(4).values(:,2)));

figure(1);
hold on;
plot(plant.time,plant.signals(3).values(:,2),'r');
hold all;
plot(plant.time,plant.signals(4).values(:,1));
end
figure(2);%semilogy(del,track_err,'so');grid on;
semilogy(del,track_err,'--gs',...
    'LineWidth',2,...
    'MarkerSize',10,...
    'MarkerEdgeColor','b',...
    'MarkerFaceColor',[0.5,0.5,0.5]);grid on;
