x0 = zeros(8,1);

%x1
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn1_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x1_min = x(1);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx1_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x1_max = x(1);
else
    'can not find a sol'
    keyboard;
end

%x2
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn2_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x2_min = x(2);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx2_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x2_max = x(2);
else
    'can not find a sol'
    keyboard;
end

%z3
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn3_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x3_min = x(3);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx3_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x3_max = x(3);
else
    'can not find a sol'
    keyboard;
end

%x4
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mn4_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x4_min = x(4);
else
    'can not find a sol'
    keyboard;
end


options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_mx4_x,x0,[],[],[],[],[],[],@confun_x,options)
if(flag==1)
    x4_max = x(4);
else
    'can not find a sol'
    keyboard;
end
%%
X_set_overbar = Polyhedron('lb',[x1_min;x2_min;x3_min;x4_min],'ub', ...
    [x1_max,x2_max,x3_max,x4_max]);
