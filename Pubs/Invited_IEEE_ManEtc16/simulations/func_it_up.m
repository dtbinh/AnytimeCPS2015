function [alpha] = func_it_up(vp,mp)
f = 3;
%u(1) is VP, u(2) is MP
%map diff u's to alpha
if(f==1)
    deadz = 0.152; %0.152 %deadzone
    I = deadzone('ZeroInterval',[-deadz deadz]);
    vp = evaluate(I,10^7*vp); %scale VP to bring it close to [-1,1]
    %vp = evaluate(I,.33*10^5*mp); %mp only
    alpha = abs(vp)+0*deadz;
    if(alpha<.001)
        alpha = 0.001;
    else
        if(alpha>1)
            alpha=1;
        end
    end
end

if(f==2)
    deadz = 0.152; %0.152 %deadzone
    I = deadzone('ZeroInterval',[-deadz deadz]);
    vp = evaluate(I,(1/1.6)*10^5*mp); %scale VP to bring it close to [-1,1]
    %vp = evaluate(I,.33*10^5*mp); %mp only
    alpha = abs(vp)+0*deadz;
    if(alpha<.001)
        alpha = 0.001;
    else
        if(alpha>1)
            alpha=1;
        end
    end
    
    
    
end

if(f==3)
    deadz = 0.102; %0.152 %deadzone
    I = deadzone('ZeroInterval',[-deadz deadz]);
    vp = evaluate(I,.5*(1/1.6)*10^5*abs(mp)+.5*10^7*abs(vp)); %scale VP to bring it close to [-1,1]
    %vp = evaluate(I,.33*10^5*mp); %mp only
    alpha = abs(vp)+0*deadz;
    if(alpha<.001)
        alpha = 0.001;
    else
        if(alpha>1)
            alpha=1;
        end
    end
    
    
    
end