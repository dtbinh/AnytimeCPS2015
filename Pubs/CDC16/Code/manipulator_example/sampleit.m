g = 9.8;
m = 1/g;
L = 1;
k = 200;
I = 300;
J = 1;
PI = 3.14;

a  = -m*g*L/I;
b = -k/I;
c  = k/J;
d = 1/J;

xbounds = [-0.12, 0.12;
    -0.05, 0.05; 
    0.1, 0.2;
    0.1, 0.2];
ubounds = [0.1, 0.9];
% xstep = [0.01, 0.01, 0.05, 0.05]';
xstep = xbounds(:,2)-xbounds(:,1);
ustep = 0.8;

% max derivative

nx = floor((xbounds(:,2)-xbounds(:,1))./xstep);
nu = floor((ubounds(:,2)-ubounds(:,1))./ustep);
store = zeros(prod(nx)*prod(nu),4);
g = @(t,x,u) [x(2); a*sin(x(1))+b*(x(1)-x(3)); x(4); c*(x(1)-x(3)) + d*u];
ii=1;
figure;hold on;
for x1=xbounds(1,1):xstep(1):xbounds(1,2)
    for x2=xbounds(2,1):xstep(2):xbounds(2,2)
        for x3=xbounds(3,1):xstep(3):xbounds(3,2)
            for x4=xbounds(4,1):xstep(4):xbounds(4,2)
                for u=ubounds(1):ustep:ubounds(2)
                    initX = [x1;x2;x3;x4];
                    f = @(t,x) g(t,x,u);
                    s = ode45(f,[0,1],initX);
                    plot(s.y(1,:),s.y(2,:));
                    store(ii,:) = s.y(:,end)';
                    ii=ii+1;
                end
            end
        end
    end
end

% Bounds of sampled reach set
M = max(store);
m = min(store);

% figure;
% hold on;
% Bounds of initial set
plot(xbounds(1,1), xbounds(2,1), 'ro');
plot(xbounds(1,1), xbounds(2,2), 'ro');
plot(xbounds(1,2), xbounds(2,1), 'ro');
plot(xbounds(1,2), xbounds(2,2), 'ro');

plot(store(:,1),store(:,2), 'x')

plot(M(1), 0,'sk', 'MarkerFaceColor', 'k');
plot(m(1), 0,'sk', 'MarkerFaceColor', 'k');
plot(0, M(2),'sk', 'MarkerFaceColor', 'k');
plot(0, m(2),'sk', 'MarkerFaceColor', 'k');

