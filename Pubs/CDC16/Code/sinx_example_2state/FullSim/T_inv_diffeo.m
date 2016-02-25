function x = T_inv_diffeo(z,a)

%if double
if(strcmp(class(z),'double'))
x = zeros(2,1);
if(numel(z)==2)
x(1) = z(1);
x(2) = asin(z(2)/a);
else
    'Fuck no, wrong size state'
   
end
elseif(strcmp(class(z),'Polyhedron'))
    Zset = z;
% Tinv  = [1;asin(z2/a)]
[Zrect,maxs,mins] = getRect(Zset);
Xmaxs = [maxs(1);asin(maxs(2)/a)];
Xmins = [mins(1);asin(mins(2)/a)];
Xset = Polyhedron('lb',Xmins,'ub',Xmaxs);
Xset.minHRep;
x = Xset;
else
    'the fuck is z?'
end
