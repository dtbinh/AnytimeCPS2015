function Etilde_k = get_E_tilde_bound(X_k,E,params)

[~,e_max,e_min] = getRect(E);
[~,x_max,x_min] = getRect(X_k);

e_int = interval(e_min,e_max);
x_int = interval(x_min,x_max);

e_tilde(1) = e_int(1);
e_tilde(2) = e_int(2);
e_tilde(3) = (-params.c1*cos(x_int(1))-params.c2)*e_int(2) + params.c2*e_int(3);
e_tilde(4) = (params.c1*x_int(2)*sin(x_int(1)))*e_int(1) + (-params.c1*cos(x_int(1))-params.c2)*e_int(2) + ...
    params.c3*e_int(4);

lbet = [inf(e_tilde(1));inf(e_tilde(2));inf(e_tilde(3));inf(e_tilde(4))];
ubet = [sup(e_tilde(1));sup(e_tilde(2));sup(e_tilde(3));sup(e_tilde(4))];
Etilde_k = Polyhedron('lb',lbet,'ub',ubet);
end