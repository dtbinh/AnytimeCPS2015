x0 = [0,0,0,0];     % Make a starting guess at the solution


%options = optimoptions(@fmincon,'Algorithm','sqp');
options = optimset('Algorithm','sqp');
[x,fval] = ... 
fmincon(@objfun,x0,[],[],[],[],[],[],@confun,options)

