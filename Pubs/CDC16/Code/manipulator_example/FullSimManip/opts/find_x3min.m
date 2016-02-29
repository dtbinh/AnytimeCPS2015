function x3_min = find_x3min(z,mn,mx,params)
zset  = z; 
sol = z.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_min_x3',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_min_x3',xopt);
        
        %[z3optimizer,z3min] = fmincon(@obj_set_min_z3,x0,xset.A,xset.b);
        %fmincon
        [x3optimizer,x3min] = fmincon(@obj_set_min_x3,xopt,zset.A,zset.b,[],[],[],[],@con_set_x3,options);
        if(x3min<fopt_simann)
            [xopt] = simann('obj_set_min_x3',x3optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_min_x3',xopt);
        end
        x3_min  = min(x3min,fopt_simann);

end