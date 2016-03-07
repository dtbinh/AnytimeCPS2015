function reachset = rtreach(reachHorizon, maxRunTime)

global maxNexpansions;
maxNexpansions = 100;
global maxNhbdWidth;
maxNhbdWidth = 200;
global minStepSize;
minStepSize = 1e-6;
global DEBUG;
DEBUG = 1;

sys = struct('max_derivative_function', @max_deri_arm);

xbounds = [-0.12, 0.12;
    -0.05, 0.05;
    0.1, 0.1;
    0.1, 0.1];
ubounds = [0.1, 0.9];
p = 2;
remainingRunTime = maxRunTime;
reachStepSize = 0.1*p*reachHorizon;
doneRefining = 0;
while (~doneRefining)
    reachStepSize = reachStepSize/p;
    t0 = tic;
    if DEBUG
    disp(['Lifting this rect at reachStepSize ',num2str(reachStepSize)]);
    printrect(xbounds);
    end
    reachset = facelift(sys, xbounds, ubounds, reachStepSize, reachHorizon, p);
    elapsedTime = toc(t0);
    remainingRunTime = remainingRunTime - elapsedTime;
    fprintf('%d ms: ran reachability with stepsize %.6f\n', remainingRunTime, reachStepSize);
    remainingRunTime = remainingRunTime - elapsedTime;
    if remainingRunTime <= elapsedTime
        doneRefining = 1;
        disp('Exiting because runtime ran out');
    end
end

    function debug_print(str,vars)
        if DEBUG
            fprintf(str,vars);
        end
    end
end


