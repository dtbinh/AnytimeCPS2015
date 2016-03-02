x0 = zeros(8,1);  
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun,x0,[],[],[],[],[],[],@confun_violator,options)
if(flag==1)
    z4_max = x(8);
else
    'can not find a sol,i.e. no violator'
    keyboard;
end