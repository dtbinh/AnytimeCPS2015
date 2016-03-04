%x0 =  zeros(8,1);  
load('SetsAndParams_Z');
x0 = [X_set_overbar.b(1:4);T_diffeo(X_set_overbar.b(1:4),params)]; %max distance member
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun_x,x0,[],[],[],[],[],[],@confun_violator_x,options)
if(flag==1)
    
else
    'can not find a sol,i.e. no violator'
    %keyboard;
end