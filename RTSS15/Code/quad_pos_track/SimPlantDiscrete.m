%init params
PlantModelQuadSimpleLinear;
x=[0;0;0;0;0;0]; %xinit
SimSteps = 750;
Params.A = sys_d.a;
Params.B = sys_d.b;
Params.Q = diag([10;10;10;1;1;1]);
Params.R = diag([.1;.1;.1]);
Params.Q_final = diag([1;1;1;1;1;1]);
Params.u_limit = [deg2rad(30);deg2rad(30);10];
Params.x_limit = [100*ones(3,1);100*ones(3,1)];
Params.x_ref=[10;10;10;0;0;0];
x_store = zeros(numel(x),SimSteps+1);
u_store = zeros(size(sys_d.b,2),SimSteps);

x_store(:,1) = x;


for i=1:SimSteps
    i
    Params.x_0 = x;
    [vars,status] = cvxsolve(Params,[]);
    x = sys_d.a*x + sys_d.b*vars.u_0;
    %store
    x_store(:,i+1) = x;
    u_store(:,i) = vars.u_0;
    
end

% plot
subplot(2,1,1);
title('Positions');
plot((1:SimSteps+1)*h,x_store(1,:));hold all;grid on;
plot((1:SimSteps+1)*h,x_store(2,:));hold all;
plot((1:SimSteps+1)*h,x_store(3,:));hold all;

subplot(2,1,2);
title('Velocities');
plot((1:SimSteps+1)*h,x_store(4,:));hold all;grid on;
plot((1:SimSteps+1)*h,x_store(5,:));hold all;
plot((1:SimSteps+1)*h,x_store(6,:));hold all;

figure
plot((1:SimSteps)*h,u_store(1,:));
hold all;grid on;
plot((1:SimSteps)*h,u_store(2,:));hold all;
plot((1:SimSteps)*h,u_store(3,:))
