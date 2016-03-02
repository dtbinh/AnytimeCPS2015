x0 = zeros(8,1);

%z1
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn1,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z1_min = x(5);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx1,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z1_max = x(5);
else
    'can not find a sol'
    keyboard;
end

%z2
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn2,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z2_min = x(6);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx2,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z2_max = x(6);
else
    'can not find a sol'
    keyboard;
end

%z3
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn3,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z3_min = x(7);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx3,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z3_max = x(7);
else
    'can not find a sol'
    keyboard;
end

%z4
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn4,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z4_min = x(8);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx4,x0,[],[],[],[],[],[],@confun,options)
if(flag==1)
    z4_max = x(8);
else
    'can not find a sol'
    keyboard;
end
%%
Z_set_overbar = Polyhedron('lb',[z1_min;z2_min;z3_min;z4_min],'ub', ...
    [z1_max,z2_max,z3_max,z4_max]);
