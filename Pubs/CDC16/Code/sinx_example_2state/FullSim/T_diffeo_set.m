function Zset = T_diffeo_set(Xset,a)
%% T  = [1;a*sin(x2)]
[Xrect,maxs,mins] = getRect(Xset);
Zmaxs = [maxs(1);a*sin(maxs(2))];
Zmins = [mins(1);a*sin(mins(2))];
Zset = Polyhedron('lb',Zmins,'ub',Zmaxs);
Zset.minHRep;
