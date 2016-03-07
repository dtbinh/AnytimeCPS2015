function fp = facepackage(f)
fp.f        = f;
fp.dim      = ceil(f/2);
fp.isMin    = mod(f,2);
switch fp.isMin
    % dix is the index, 1 or 2, of bound needing change
    case 1
        fp.dix = 1; % min
    case 0
        fp.dix = 2; % max
    otherwise
        error('huh?');
end