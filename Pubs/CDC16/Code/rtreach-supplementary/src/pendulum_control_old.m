function uout  = pendulum_control(x, kg, n)
    %region based on x'*P*x<1: have to check current controller to determine
    %proper P to use    
    %uout = x(1,1)*kg(1,n)+x(2,1)*kg(1,2,n)+x(3,1)*kg(1,3,n)+x(4,1)*kg(1,4,n);
    uout = sum(x .* kg(:,n));