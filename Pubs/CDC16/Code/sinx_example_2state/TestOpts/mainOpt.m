x0 = [0,0,0,0];     % Make a starting guess at the solution

x0 = zeros(8,1);
%options = optimoptions(@fmincon,'Algorithm','sqp');
options = optimset('Algorithm','sqp');
[x,fval,flag] = ... 
fmincon(@objfun,x0,[],[],[],[],[],[],@confun_violator,options)