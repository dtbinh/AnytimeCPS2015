function z = T_diffeo(x,params)
optim_based = 0;
if(strcmp(class(x),'double'))
    if(numel(x)==4)
        z = zeros(4,1);
        z(1) = x(1);
        z(2) = x(2);
        z(3) = -params.c1*sin(x(1))-params.c2*(x(1)-x(3));
        z(4) = -params.c1*x(2)*cos(x(1)) - params.c2*(x(2)-x(4));
    else
        'fuck no! wrong size state bro'
    end
    
elseif(strcmp(class(x),'Polyhedron'))
    [xrect,mx,mn] = getRect(x);
    x_1 = interval(mn(1),mx(1));
    x_2 = interval(mn(2),mx(2));
    x_3 = interval(mn(3),mx(3));
    x_4 = interval(mn(4),mx(4));
    %use b4m
    z_1 = x_1;
    z_2 = x_2;
    z_3 = -params.c1*sin(x_1) - params.c2*(x_1-x_3);
    z_4 = -params.c1*x_2*cos(x_1) - params.c2*(x_2-x_4);
    z = Polyhedron('lb',[inf(z_1),inf(z_2),inf(z_3),inf(z_4)],'ub', ...
        [sup(z_1),sup(z_2),sup(z_3),sup(z_4)]);
    %use optimization
    if(optim_based==1)
        xset = x;
        save('SetsAndParams','params','xset','-append');
        z3_min = find_z3min(x,mn,mx,[]);
        z3_max = find_z3max(x,mn,mx,[]);
        z4_min = find_z4min(x,mn,mx,[]);
        z4_max = find_z4max(x,mn,mx,[]);
        z = Polyhedron('lb',[inf(z_1),inf(z_2),z3_min,z4_min],'ub', ...
            [sup(z_1),sup(z_2),z3_max,z4_max]);
        
    end
else
    'The fuck is x?'
end


end


