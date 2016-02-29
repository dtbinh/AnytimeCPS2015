function z4_max = find_z4max(x,mn,mx,params)
xset  = x; 
sol = x.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_max_z4',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_max_z4',xopt);
        
        %[z4optimizer,z4min] = fmincon(@obj_set_min_z4,x0,xset.A,xset.b);
        %fmincon
        [z4optimizer,z4max] = fmincon(@obj_set_max_z4,xopt,xset.A,xset.b,[],[],[],[],@con_set_z4,options);
        if(z4max<fopt_simann)
            [z4max fopt_simann]
            're-search'
            [xopt] = simann('obj_set_min_z4',z4optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_min_z4',xopt);
        end
        z4_max  = -min(z4max,fopt_simann);

end