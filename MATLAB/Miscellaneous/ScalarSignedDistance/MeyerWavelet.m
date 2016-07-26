function [phi,psi] = MeyerWavelet(t)
%Meyer wavelet (psi) and scale (phi) as in Valenzuela and Oliviera

if(t==0)
    phi = 2/3 + 4/(3*pi);
else
    phi = (sin((2*pi/3)*t) + (4*t/3)*cos(4*pi*t/3))/ ...
        (pi*t-(16*pi*t^3)/9);
end

psi_1_num = (4/(3*pi))*(t-0.5)*cos((2*pi/3)*(t-0.5))- ...
    (1/pi)*sin((4*pi/3)*(t-0.5));
psi_1_den = (t-0.5)-(16/9)*(t-0.5)^3;

psi_2_num = (8/(3*pi))*(t-0.5)*cos((8*pi/3)*(t-0.5))+ ...
    (1/pi)*sin((4*pi/3)*(t-0.5));
psi_2_den = (t-0.5)-(64/9)*(t-0.5)^3;

psi_1 = psi_1_num/psi_1_den;
psi_2 = psi_2_num/psi_2_den;

psi = psi_1 + psi_2;
