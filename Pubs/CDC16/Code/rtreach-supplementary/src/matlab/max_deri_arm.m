function der = max_deri_arm(sys, ubounds, nhbd, facepkg)


g = 9.8;
m = 1/g;
L = 1;
k = 1;
I = 1;
J = 1;

f = facepkg.f;
dim = facepkg.dim;
dix = facepkg.dix;
isMin = facepkg.isMin;
c  = k/J;
a  = -m*g*L/I;
b  = -k/I;
d  = 1/J;
der = 0;
%     // This only maximizes the derivative of the ith state variable, where i = dim = faceIndex /2
%     // This is equivalent to maximizing the projection of the gradient onto the ith dimension.
%     // Note that we want to maximize the _outward_ derivative, as in "outward from a face": for a min face, this is the smallest signed derivate (leading the system
%     // further back), and for a max face, this is the largest signed derivative.

m1 = nhbd(1,1);
M1 = nhbd(1,2);
m3 = nhbd(3,1);
M3 = nhbd(3,2);

if (dim == 1)  %  x1
    der = nhbd(2,dix);
    
elseif (dim == 2)
    % x2' = -b*x3 + b*x1 + a*sin(x1) = -b*x3+f(x1)
    % Two solutinos to a*cos(x1) + b = 0 (assuming |b/a| <1)
    x1  = acos(-b/a); % \in [pi/2,pi]
    x0  = -x1;
    fx0 = b*x0 + a*sin(x0);
    fm1 = b*m1 + a*sin(m1);
    fM1 = b*M1 + a*sin(M1);
    if (isMin)
        % min face so want the smallest (signed) derivative
        if (abs(b/a) > 1)
            % f'(x1) = b + a*cos(x1) does not become 0
            der = min(fm1, fM1);
        elseif (m1 <= x1 && M1 > x1)
            der = fx1;
        elseif (-pi <= m1 && M1 <= pi)
            der = min(fm1, fM1);
        else
            printf('CRAP!!! At max face %d, der = %f, x0=%f, x1=%f, m1=%f, M1=%f \n', f, der , x0, x1, m1, M1);
        end
        der  = -b*m3 + der;
        
    else % if not min
        % max face so want largest derivative
        if (abs(b/a) > 1)
            % f'(x1) = b + a*cos(x1) does not become 0
            der = max(fm1, fM1);
        elseif (m1 <= x0 && M1 >= x0)
            der = fx0;
        elseif (-pi <= m1 && M1 <= pi)
            der = max(fm1, fM1);
        else
            printf('CRAP!!! At max face %d, der = %f, x0=%f, x1=%f, m1=%f, M1=%f \n', f, der , x0, x1, m1, M1);
        end
        der  = -b*M3 + der;
        
    end
elseif (dim == 3)
    der = nhbd(4,dix);
    
elseif (dim==4)
    if (isMin)
        der = c*(m1-M3) + d*ubounds(1);
    else
        der = c*(M1-m3) + d*ubounds(2);
    end
end
