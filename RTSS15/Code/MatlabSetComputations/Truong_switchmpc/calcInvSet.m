function [Cinv, status] = calcInvSet( sys, ZN, LNF, wmax, epsilon, pw, pe, tmax, method)
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
    assert(method == 1, 'Currently only method 1 is supported.');
    % assert(method == 1 || method == 2, 'Parameter method is invalid.');
end

% Common parameters and values
[nx, nu] = size(sys.B1);
Ahat =  [sys.A, sys.B1; zeros(nu, nx+nu)];
Bhat = [sys.B2; eye(nu)];

qw = supportFunNorm(pw);
qe = supportFunNorm(pe);

% if LNF ~ 0 then we don't need to consider the disturbances What
hasWhat = ~all(all(abs(LNF) < eps));

curIter = 1;

% Initially Cinv is ZN, then we compute one-step step iteratively
Cinv = ZN;
PCinv = Polyhedron(Cinv.H, Cinv.K);  % PCinv is always the current step's Cinv, used to compare sets

%allCinv(1) = Cinv;

while curIter <= tmax
    fprintf('Iteration %d...\n', curIter);
    
    % Compute T = Cinv - (LNF*What)
    T = Cinv;
    if hasWhat
        % Compute T using support function of What
        T.K = Cinv.K -...
              colfun((Cinv.H*LNF).',...
                     @(eta) (wmax*norm(eta,qw) +...
                             epsilon*(norm(sys.A.'*eta,qe) + norm(-eta,qe)))...
                    );
                
        % minimal rep
        PT = minHRep(Polyhedron(T.H, T.K));
        if PT.isEmptySet
            disp('PT');
            status = -1;
            return;
        end
        T = poly2struct(PT);
%     else
%         if method == 2
%             PT = Polyhedron(Cinv.H, Cinv.K);
%         end
    end

    % Compute the one-step set
    switch method
        case 1
            % Construct Phi polyhedron and intersect it with ZN
            Phi = Polyhedron(...
                [T.H*[Ahat, Bhat]; ZN.H, zeros(size(ZN.H, 1), nu)],...
                [T.K; ZN.K]);
            % Phi.minHRep;
%             Phi = Polyhedron(T.H*[Ahat, Bhat], T.K);
%             Phi.minVRep;
%             Phi = Phi.projection(1:(nx+nu));
%             Phi = intersect(Phi, PZN);
            if Phi.isEmptySet
                disp('Phi');
                status = -1;
                return;
            end
            % Phi.minVRep;
            % PnextCinv = Phi;
            PnextCinv = Phi.projection(1:(nx+nu));  % project Phi to the Z dimensions to obtain 
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
    
    % Now PnextCinv is the one-step set, we check if we can stop
    if PCinv == PnextCinv
        status = 0;
        return;
    end
    
    % If not, set Cinv to nextCinv and repeat
    PCinv = PnextCinv;
    Cinv = poly2struct(PCinv);
    
    curIter = curIter + 1;
    
    %allCinv(curIter) = Cinv;
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