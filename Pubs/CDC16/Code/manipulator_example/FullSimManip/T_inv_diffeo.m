function x = T_inv_diffeo(z,params)
optim_based = 0;
if(strcmp(class(z),'double'))
    if(numel(z)==4)
        x = zeros(4,1);
        x(1) = z(1);
        x(2) = z(2);
        x(3) = (1/params.c2)*(z(3) + params.c1*sin(z(1)) + params.c2*z(1));
        x(4) = (1/params.c2)*(z(4) + params.c2*z(2)*cos(z(1)) + params.c2*z(2));
    else
        'fuck no! wrong size state bro'
    end
    
elseif(strcmp(class(z),'Polyhedron'))
    [zrect,mx,mn] = getRect(z);
    z_1 = interval(mn(1),mx(1));
    z_2 = interval(mn(2),mx(2));
    z_3 = interval(mn(3),mx(3));
    z_4 = interval(mn(4),mx(4));
    %use b4m
    x_1 = z_1;
    x_2 = z_2;
    x_3 = (1/params.c2)*(z_3 + params.c1*sin(z_1) + params.c2*z_1);
    x_4 = (1/params.c2)*(z_4 + params.c2*z_2*cos(z_1) + params.c2*z_2);
    x = Polyhedron('lb',[inf(x_1),inf(x_2),inf(x_3),inf(x_4)],'ub', ...
        [sup(x_1),sup(x_2),sup(x_3),sup(x_4)]);
    if(optim_based)
        zset = z;
        save('SetsAndParams','params','zset','-append');
        x3_min = find_x3min(z,mn,mx,[]);
        x3_max = find_x3max(z,mn,mx,[]);
        x4_min = find_x4min(z,mn,mx,[]);
        x4_max = find_x4max(z,mn,mx,[]);
        z = Polyhedron('lb',[inf(x_1),inf(x_2),x3_min,x4_min],'ub', ...
            [sup(x_1),sup(x_2),x3_max,x4_max]);
    end
    
else
    'The fuck is z?'
end


end


