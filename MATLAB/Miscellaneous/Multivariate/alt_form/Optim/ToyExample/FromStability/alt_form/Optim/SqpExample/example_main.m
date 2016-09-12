x0 = [-1,1];            % Starting guess 
options = optimoptions(@fmincon,'Algorithm','sqp');
options = optimoptions(options,'SpecifyObjectiveGradient',false,'SpecifyConstraintGradient',false,'Display','iter');
lb = [ ]; ub = [ ];   % No upper or lower bounds
[x,fval,flag,output] = fmincon(@objfungrad,x0,[],[],[],[],lb,ub,... 
   @confungrad,options);
