function [reachset, reachsetValid] = facelift(sys, xbounds, ubounds, reachStepSize, reachHorizon, p)

global minStepSize;
global DEBUG;

% Consume at least reachStepSize/p seconds every time the rectangle is
% lifted.

dimX                = size(xbounds,1);
nfaces              = 2*dimX;
remReachTime        = reachHorizon;
liftedRect          = xbounds;
crossTime           = inf;
reachsetValid       = 1;
maxders             = zeros(1,nfaces);
reachset            = zeros(dimX,2);
elapsedReachTime    = 0;
liftedrects         = {xbounds};
nsteps = 1;

while (remReachTime > 0 && reachsetValid)
    nsteps = nsteps + 1;
    thisReachStep = min(reachStepSize, remReachTime);
    if (thisReachStep < minStepSize && remReachTime < minStepSize)
        fprintf('Stopping because reachStep %f < minStepSize %f\n',thisReachStep, minStepSize);
        break;
    end
    for f=1:nfaces
        [maxder, nhbdWidth, valid] = lift_one_face(sys, f, liftedRect, ubounds, thisReachStep, p);
        if valid
            maxders(f) = maxder;
            faceCrossTime = nhbdWidth/abs(maxder);
            % Sanity check that we are at least consuming reachStep/p by
            % making this lift. The only exception is if the remaining
            % reach time is less than that, in which case it's fine to only
            % consume remainingReachTime
            assert(remReachTime <= reachStepSize/p || faceCrossTime >= reachStepSize/p, sprintf('crossTime %f smaller than it should be.\n', crossTime));
            % The minimum crossTime accross all faces is what we use.
            crossTime = min(faceCrossTime, crossTime);           
        else
            reachsetValid = 0;
            break;
        end
    end
    if reachsetValid        
        for f=1:nfaces
            fp = facepackage(f);
            liftedRect(fp.dim,fp.dix) = liftedRect(fp.dim,fp.dix) + maxders(f)*crossTime;            
        end
        remReachTime = remReachTime - crossTime;
        elapsedReachTime = reachHorizon - remReachTime;
        if DEBUG
            liftedrects{nsteps} = liftedRect;
            fprintf('Reachtime %d: Valid lifted rect at step size %f:\n', elapsedReachTime, reachStepSize);
        end
        
    end
end

if DEBUG
    colors = {'red', 'black', 'blue', 'green', 'yellow', 'magenta'};
    nc = length(colors);
    alpha = 1:-1/length(liftedrects):0.01;
    for lr = 1:length(liftedrects)
        printrect(liftedrects{lr}, 'p', 'Alpha', alpha(lr),'Color', colors{mod(lr,nc)+1});  
        hold on;
    end
end
