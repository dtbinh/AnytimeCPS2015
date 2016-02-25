function Xset = T_inv_diffeo_set(Zset,a)
%% Tinv  = [1;asin(z2/a)]
[Zrect,maxs,mins] = getRect(Zset);
Xmaxs = [maxs(1);asin(maxs(2)/a)];
Xmins = [mins(1);asin(mins(2)/a)];
Xset = Polyhedron('lb',Xmins,'ub',Xmaxs);
Xset.minHRep;
