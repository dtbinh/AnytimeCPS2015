

g = 9.8;
m = 1/g;
L = 1;
k = 200;
I = 300;
J = 1;
PI = 3.14;


xrange = {-0.12:0.05:0.12;
    -0.05:0.01:0.05;
    0.1:0.05:0.2;
    0.1:0.05:0.2};

ii=1;
urange = 0.1:0.1:0.9;
n = length(xrange{1})*length(xrange{2})*length(xrange{3})*length(xrange{4})*length(urange);
store = zeros(n,4);
for x1=xrange{1}
    for x2=xrange{2}
        for x3=xrange{3}
            for x4=xrange{4}
                for u=urange
                    x = [x1;x2;x3;x4];
                    f = @(t,x) [x(2);-(m*g*L/I)*sin(x(1)) - (k/I)ß*(x(1)-x(3)); x(4); k*(x(1)-x(3))/J + u/J];
                    s = ode45(f,[0,1],x);
                    store(ii,:) = s.y(:,end)';
                    ii=ii+1;
                end
            end
        end
    end
end

M = max(store);
m = min(store);
figure;
hold on;
plot(xrange{1}(1), xrange{2}(1),'ro', 'MarkerFaceColor', 'r');
plot(xrange{1}(1), xrange{2}(end),'ro', 'MarkerFaceColor', 'r');
plot(xrange{1}(end), xrange{2}(1),'ro', 'MarkerFaceColor', 'r');
plot(xrange{1}(end), xrange{2}(end),'ro', 'MarkerFaceColor', 'r');
plot(store(:,1), store(:,2), 'x');
