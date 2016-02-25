function z = T_diffeo(x,a)
if(strcmp(class(x),'double'))
    z = zeros(2,1);
    if(numel(x)==2)
        z(1) = x(1);
        z(2) = a*sin(x(2));
    else
        'Fuck no, wrong size state'
    end
    
elseif(strcmp(class(x),'Polyhedron'))
    Xset = x;
    % T  = [1;a*sin(x2)]
    [Xrect,maxs,mins] = getRect(Xset);
    Zmaxs = [maxs(1);a*sin(maxs(2))];
    Zmins = [mins(1);a*sin(mins(2))];
    Zset = Polyhedron('lb',Zmins,'ub',Zmaxs);
    Zset.minHRep;
    z = Zset;
else
    'The fuck is x?'
end