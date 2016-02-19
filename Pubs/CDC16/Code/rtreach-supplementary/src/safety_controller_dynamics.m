function [ out ] = safety_controller_dynamics( ~, X )

A = [0 1 0 0 ; 
    0 -10.95 -2.75 0.0043 ;
    0 0 0 1 ;
    0 24.92 28.58 -0.044
    ];

B = [0 ; 1.94 ; 0 ; -4.44 ];

K_lmi = [  0.4072  7.2373 18.6269   3.6725  ];

K = K_lmi;

u = K*X;

if (u < -4.95)
    u = -4.95;
elseif (u > 4.95)
    u = 4.95;
end

out = A*X + B*u;

%out = (A + B * K) * X;

end

