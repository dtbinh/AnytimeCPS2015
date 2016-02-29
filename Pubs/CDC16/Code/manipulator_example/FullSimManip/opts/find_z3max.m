function z3_max = find_z3max(x,mn,mx,params)
xset  = x; 
sol = x.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_max_z3',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_max_z3',xopt);
        
        %[z3optimizer,z3min] = fmincon(@obj_set_min_z3,x0,xset.A,xset.b);
        %fmincon
        [z3optimizer,z3max] = fmincon(@obj_set_max_z3,xopt,xset.A,xset.b,[],[],[],[],@con_set_z3,options);
        if(z3max<fopt_simann)
            [xopt] = simann('obj_set_min_z3',z3optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_min_z3',xopt);
        end
        z3_max  = -min(z3min,fopt_simann);

end