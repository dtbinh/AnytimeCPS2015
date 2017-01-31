function [phi] = MeyerWavelet_phi(t)
%% Meyer wavelet (psi) and scale (phi) as in Valenzuela and Oliviera
a1 = (2*pi)/3;
a2 = 4/3;
a3 = 4*pi/3;
a4 = pi;
a5 = (16*pi)/9;


if(t==0 || t==sqrt(a4/a5)|| t==-sqrt(a4/a5))
    %phi = 2/3 + 4/(3*pi);
    phi = (a1*cos(a1*t) + a2*cos(a3*t) - a2*a3*t*sin(a3*t))/ ...
        (a4-3*a5*t^2);
else
    phi = (sin((2*pi/3)*t) + (4*t/3)*cos(4*pi*t/3))/ ...
        (pi*t-(16*pi*t^3)/9);
end
