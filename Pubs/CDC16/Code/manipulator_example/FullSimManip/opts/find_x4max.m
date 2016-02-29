function x4_max = find_x4max(z,mn,mx,params)
zset  = z; 
sol = z.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_max_x4',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_max_x4',xopt);
        
        %[z3optimizer,z3max] = fmaxcon(@obj_set_max_z3,x0,xset.A,xset.b);
        %fmaxcon
        [x4optimizer,x4max] = fmincon(@obj_set_max_x4,xopt,zset.A,zset.b,[],[],[],[],@con_set_x4,options);
        if(x4max<fopt_simann)
            [xopt] = simann('obj_set_max_x4',x4optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_max_x4',xopt);
        end
        x4_max  = -min(x4max,fopt_simann);

end