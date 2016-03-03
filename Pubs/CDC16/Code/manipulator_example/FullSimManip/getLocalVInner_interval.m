function V_inner_local = getLocalVInner_interval(X_k,U,params)
%function V_inner_local = getLocalVInner_interval(X_k,U,params)

[~,xk_max,xk_min] = getRect(X_k);
[~,u_mx,u_mn] = getRect(U);
x = interval(xk_min,xk_max);
u = interval(u_mn,u_mx);
%params
c1 = params.c1;
c2 = params.c2;
c3 = params.c3;
c4 = params.c4;
c5 = params.c5;

alpha_int = c1*(x(2)^2)*sin(x(1)) - (c1*cos(x(1))-c2)*(c1*sin(x(1))+c2*(x(1)-x(3))) + c3*(x(1)-x(3));
%v_int = c4*u + alpha_int; %no, this is only outer approx sir

v_low = c4*u_mn + sup(alpha_int);
v_high = c4*u_mx + inf(alpha_int);

V_inner_local = Polyhedron('lb',v_low,'ub',v_high);
