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

xbounds = [-PI, PI;
    -PI, PI; 
    -1, 1;
    -1, 1];
ubounds = [0.1, 0.5];
xbounds = 0.2*xbounds;
ubounds = 0.2*ubounds;
xstep = 0.1;
ustep = 0.05;

figure;
hold on;
plot(xbounds(1,1), xbounds(2,1), 'ro');
plot(xbounds(1,1), xbounds(2,2), 'ro');
plot(xbounds(1,2), xbounds(2,1), 'ro');
plot(xbounds(1,2), xbounds(2,2), 'ro');
g = @(t,x,u) [x(2); a*sin(x(1))+b*(x(1)-x(3)); x(4); c*(x(1)-x(3)) + d*u];
for x1=xbounds(1,1):xstep:xbounds(1,2)
    for x2=xbounds(2,1):xstep:xbounds(2,2)
        for x3=xbounds(3,1):xstep:xbounds(3,2)
            for x4=xbounds(4,1):xstep:xbounds(4,2)
                for u=ubounds(1):ustep:ubounds(2)
                    initX = [x1;x2;x3;x4];
                    f = @(t,x) g(t,x,u);
                    s = ode45(f,[0,1],initX);
                    plot(s.y(1,:), s.y(2,:));
                end
            end
        end
    end
end

