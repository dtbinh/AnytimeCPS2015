function [Cinv, status, Phi] = calcInvSet( sys, ZN, LNF, wmax, epsilon, pw, pe, tmax, method)
%CALCINVSET Calculate the invariant set C for terminal set, for fixed K.
%   
%   tmax: max number of iterations.
%   method: method to compute one-step set (1: via projection, 2: via
%           Minkowski sum); default: 1.
%
%   status: 0: succeful; 1: tmax reached without success; -1: failed for
%           other reason (e.g. some set becomes empty, Cinv may not exist).
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

if ~exist('method', 'var')
    method = 1;
else
    assert(method == 1 || method == 2, 'Parameter method is invalid.');
end

[nx, nu] = size(sys.B1);
Ahat =  [sys.A, sys.B1; zeros(nu, nx+nu)];
Bhat = [sys.B2; eye(nu)];

qw = supportFunNorm(pw);
qe = supportFunNorm(pe);

% if LNF ~ 0 then we don't need to consider the disturbances What
hasWhat = ~all(all(abs(LNF) < eps));

Cinv = ZN;
PZN = Polyhedron(ZN.H, ZN.K);
PZN.minHRep();

if method == 2
    % Input constraint is the projection of PZN onto u
    PU = PZN.projection((nx+1):(nx+nu));
    if PU.isEmptySet
        status = -1;
        return;
    end
    
    % Compute -Bhat*U for method 2
    PBU = (-Bhat)*PU;
    PBU.minHRep();
end

curIter = 1;
PCinv = Polyhedron(Cinv.H, Cinv.K);

while curIter <= tmax
    fprintf('Iteration %d...\n', curIter);
    
    % Compute T = Cinv - (LNF*What)
    if hasWhat
        Cinv.K = Cinv.K -...
              colfun((Cinv.H*LNF).',...
                     @(eta) wmax*norm(eta,qw) +...
                            epsilon*(norm(sys.A.'*eta,qe) + norm(-eta,qe)));
        % minimal rep
        PT = minHRep(Polyhedron(Cinv.H, Cinv.K));
        if PT.isEmptySet
            status = -1;
            return;
        end
        Cinv.H = PT.A;
        Cinv.K = PT.b;
        if ~isempty(PT.be)
            Cinv.H = [Cinv.H; PT.Ae; -PT.Ae];
            Cinv.K = [Cinv.K; PT.be; -PT.be];
        end
    else
        if method == 2
            PT = Polyhedron(Cinv.H, Cinv.K);
        end
    end

    % Compute the one-step set
    switch method
        case 1
            % Construct Phi polyhedron and intersect it with ZN
            Phi = minHRep(Polyhedron(...
                [Cinv.H*[Ahat, Bhat]; ZN.H, zeros(size(ZN.H, 1), nu)],...
                [Cinv.K; ZN.K]));
            if Phi.isEmptySet
                status = -1;
                return;
            end
            Phi.minVRep;
            PnextCinv = Phi.projection(1:(nx+nu));
        case 2
            PTBU = PT + PBU;
            PTBU.minHRep;
            
            % We need to find the set Z such that Ahat*Z \subseteq PTBU.
            PnextCinv = PTBU.invAffineMap(Ahat);
            
            % Intersect it with ZN
            PnextCinv = intersect(PnextCinv, PZN);
            
            if PnextCinv.isEmptySet
                status = -1;
                return;
            end
    end
    
    PnextCinv.minHRep;
    
%     PU = PnextCinv.projection((nx+1):(nx+nu));
%     if PU.isEmptySet
%         status = -1;
%         disp('PU is empty.');
%         return;
%     else
%         plot(PU);
%         pause;
%         close;
%     end
    
    Cinv.H = PnextCinv.A;
    Cinv.K = PnextCinv.b;
    if ~isempty(PnextCinv.be)
        Cinv.H = [Cinv.H; PnextCinv.Ae; -PnextCinv.Ae];
        Cinv.K = [Cinv.K; PnextCinv.be; -PnextCinv.be];
    end
    
    if PCinv == PnextCinv
        status = 0;
        return;
    end
    
    PCinv = PnextCinv;
    
    curIter = curIter + 1;
end

status = 1;

end

function q = supportFunNorm(p)
    if p == 1
        q = inf;
    elseif p == 2
        q = 2;
    elseif isinf(p)
        q = 1;
    else
        error('Check the norms: they must be 1, 2, or inf.');
    end
end