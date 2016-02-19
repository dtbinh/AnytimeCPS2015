%
N = 5000;
e1 = e1_min + (e1_max-e1_min).*rand(N,1);
e2 = e2_min + (e2_max-e2_min).*rand(N,1);
x1_low = -pi/4;
x1_high = pi/4;
x2_low = -pi/3;
x2_high = -pi/4;
x1 = x1_low + (x1_high-x1_low).*rand(N,1);
x2 = x2_low + (x2_high-x2_low).*rand(N,1);

%
L = max(1,a*cos(x2_high));
E_inf_param = max([abs(e1_min),abs(e1_max),abs(e2_min),abs(e2_max)]);
E_tilde_Lip = L*Polyhedron('lb',[-E_inf_param;-E_inf_param],'ub',[E_inf_param;E_inf_param]);

%
E_tilde_Lin = Polyhedron('lb',[e1_min;a*cos(x2_high)*e2_min],'ub',[e1_max;a*cos(x2_high)*e2_max]);

%
e_tilde = [x1 a*sin(x2)] - [(x1+e1) a*sin(x2+e2)];

%plots
figure;
E_tilde_Lip.plot;hold on;
E_tilde_Lin.plot('Color','blue');
plot(e_tilde(:,1),e_tilde(:,2),'k.');
axis square
legend('Lipschitz Bounds','Linearization Bounds','Randomized errors');
