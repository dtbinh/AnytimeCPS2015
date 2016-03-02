%x0 =  zeros(8,1);  
load('SetsAndParams_Z');
x0 = [T_inv_diffeo(Z_set_overbar.b(1:4),params);Z_set_overbar.b(1:4)];
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun,x0,[],[],[],[],[],[],@confun_violator,options)
if(flag==1)
    
else
    'can not find a sol,i.e. no violator'
    %keyboard;
end