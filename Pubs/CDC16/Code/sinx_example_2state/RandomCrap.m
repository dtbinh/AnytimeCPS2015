%% optimization trial with reach based adaptive rectangular bounds on shizzle
x_min = -0.5;%-pi/4;
x_max = 0;%pi/4;

cvx_begin quiet
variable x
variable u

minimize norm(u)
subject to

f_min = (u_min+tan(x_max))*a*cos(x_max);
f_max = (u_max+tan(x_min))*a*cos(x_max);

u<=f_max;
u>=f_min;
x>=x_min;
x<=x_max;

cvx_end

%% on to reach using invset
X0 = Polyhedron('lb',[-0.1;-0.1],'ub',[0.2;0.1]);
X0.minHRep;
X0_aug = std2aug(X0.A,X0.b);
U_aug = std2aug(U.A,U.b);
E_matrix = eye(2);
W_aug = std2aug(W.A,W.b);
R = reach(A_d,B_d,E_matrix,X0_aug,U_aug,W_aug);
R_poly = Polyhedron('A',R(:,1:2),'b',R(:,3));

%% fiddadle on these sets for the rectangle from R_poly
cvx_begin 
variable x(2)
minimize -x(1) %and x(1), x(2) and -x(2)
subject to
R_poly.A*x<=R_poly.b;
cvx_end


