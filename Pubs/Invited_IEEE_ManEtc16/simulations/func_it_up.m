function [alpha] = func_it_up(vp,mp)

%u(1) is VP, u(2) is MP
%map diff u's to alpha
deadz = 0.152;
I = deadzone('ZeroInterval',[-deadz deadz]);
vp = evaluate(I,10^7*vp);
%vp = evaluate(I,.33*10^5*mp); %mp only
alpha = abs(vp)+0*deadz;
if(alpha<.1)
    alpha = 0.1;
else
if(alpha>1)
    alpha=1;
end
end