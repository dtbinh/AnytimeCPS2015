function z4_min = find_z4min(x,mn,mx,params)
xset  = x; 
sol = x.interiorPoint;
        x0 = sol.x;
        options = optimset('Algorithm','sqp');
        %simulated annealing
        [xopt] = simann('obj_set_min_z4',x0,mn,mx, ...
            1000,.5,5,20,100);
        fopt_simann = feval('obj_set_min_z4',xopt);
        
        %[z3optimizer,z3min] = fmincon(@obj_set_min_z3,x0,xset.A,xset.b);
        %fmincon
        [z4optimizer,z4min] = fmincon(@obj_set_min_z4,xopt,xset.A,xset.b,[],[],[],[],@con_set_z4,options);
        if(z4min<fopt_simann)
            [xopt] = simann('obj_set_min_z4',z4optimizer,mn,mx, ...
                1000,.5,5,20,100);
            fopt_simann = feval('obj_set_min_z4',xopt);
        end
        z4_min  = min(z4min,fopt_simann);

end