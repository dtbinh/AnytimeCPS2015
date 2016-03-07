function [maxder, nhbdWidth, valid] = lift_one_face(sys, f, rect, ubounds, thisReachStep, p)

global maxNexpansions;
global maxNhbdWidth;

valid           = 1;
facepkg = facepackage(f);
dim = facepkg.dim;
isMin = facepkg.isMin;
dix = facepkg.dix;

nhbd = rect;
if isMin
    nhbd(dim,2) = nhbd(dim,1);
    
else
    nhbd(dim,1) = nhbd(dim,2);
end

max_derivative = sys.max_derivative_function;
der = max_derivative(sys, ubounds, nhbd, facepkg);
nhbd(dim, dix) = nhbd(dim,dix) + der*thisReachStep;

needsExpansion = 1;
prevder = der;
prevGrowsOutward = isMin && prevder <=0 || ~isMin && prevder >= 0;
nexpansions = 0;
while (needsExpansion && nexpansions < maxNexpansions && abs(prevder)*thisReachStep < maxNhbdWidth)
    nexpansions = nexpansions + 1;
    
    der = max_derivative(sys, ubounds, nhbd, facepkg);
    
    growsOutward = isMin && der <=0 || ~isMin && der >= 0;    
    if growsOutward && ~prevGrowsOutward
        needsExpansion = 1;
    elseif isMin &&  ((der < 0 && prevder <= 0 && der < p*prevder) || (der > 0 && prevder > 0 && der < prevder/p))
        needsExpansion = 1;
    elseif ~isMin && ((der >0 && prevder >= 0 && der > p*prevder) || (der < 0 && prevder <0 && der > prevder/p))
        needsExpansion = 1;
    else
        needsExpansion = 0;
    end
    if needsExpansion
        nhbd(dim,dix) = nhbd(dim,dix) + der*thisReachStep;
        prevder = der;
        prevGrowsOutward = growsOutward;
    end
    
end

if needsExpansion
    valid = 0;
end
maxder = der;
nhbdWidth = abs(der)*thisReachStep ;
1;
