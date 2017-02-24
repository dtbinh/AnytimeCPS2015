function smoothie
n = 2;
A = [0 1
    0 -1
    1 0
    -1 0
    ];
b = [1; 1; 1; 1];
% Square is centered at 0 and extends along the x-axis from S(1) to S(2)
% and along the y-axis from S(3) to S(4)
S = [-1, 1, -1, 1];
dx = 0.1;
B = 2;
N = length(-B:dx:B);
i=N;j=1;
F = zeros(N);
Je = F;
J = J;
epsi = 0.1;
for x1=-B:dx:B
    for x2=-B:dx:B
        xx = [x1;x2];
        F(i,j) = distFromSquare(xx,S);
%         F(i,j) = DistFromPolyhedra(xx,A,b);
        Je(i,j) = (1/epsi^n)*jay(xx/epsi);
        J(i,j) = jay(xx);
        i = i-1;
    end
    j = j+1;
    i = N;
end

Fe = conv2(F, Je, 'same');
c = max(max(abs(F)))/max(max(abs(Fe)));
Fe = c*Fe;
surf(Fe); title('Smoothed dist')
max(max(abs(F-Fe)))

1;

    function dist = distFromSquare(xx, S)
        inset = 0;
        if (xx(1) >= S(1) && xx(1) <= S(2)) % horizontally in square bounds
            if xx(2) <= S(4) && xx(2) >= S(3) % vertically in sq bounds
                % use this for dist fnt
%                 dist = 0;
                % use this instead for signed distance
                d1 = min([abs(xx(1)-S(1)), abs(xx(1)-S(2)),...
                    abs(xx(2)-S(2)), abs(xx(2)-S(4))]);
                dist = d1;
                inset = 1;
            else
                dist = min(abs([xx(2)-S(3), xx(2) - S(4)]));
            end                            
        elseif (xx(2) >= S(3) && xx(2) <= S(4))            
            dist = min(abs([xx(1)-S(1), xx(1) - S(2)]));           
        else
            dist = norm(abs(xx)-[1;1]);
        end
        if ~inset
            dist = -dist;
        end
    end
    function y = h(x)
        if x <= 0
            y=0;
        else
            y = exp(-1/x^2);
        end
    end
    function y = jay(x)        
        y = h(1-norm(x)^2);
    end
end