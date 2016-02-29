function x4_min = find_x4min(z,mn,mx,params)
zset  = z; 
sol = z.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_min_x4',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_min_x4',xopt);
        
        %[z3optimizer,z3min] = fmincon(@obj_set_min_z3,x0,xset.A,xset.b);
        %fmincon
        [x4optimizer,x4min] = fmincon(@obj_set_min_x4,xopt,zset.A,zset.b,[],[],[],[],@con_set_x4,options);
        if(x4min<fopt_simann)
            [xopt] = simann('obj_set_min_x4',x4optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_min_x4',xopt);
        end
        x4_min  = min(x4min,fopt_simann);

end