function [hull, area] = graham_scan(X,nr,nc)
% hull = graham_scan(X,nr,nc)
% 
% Computes the convex hull of the data set in X using Graham's scan
% algorithm. See http://geomalgorithms.com/a10-_hull-1.html
%
% X is n-by-2 set of n points in pixel coordinates
% [nr,nc] is the size of the image from which X comes.
% hull is the convex hull of X, m-by-2, each row is the coordinate of a
% hull pixel.

nbpoints = size(X,1);
% find the lowest, rightmost point
m = max(X(:,1));
ff = find(X(:,1)==m);
lowestPnts = X(ff,:);
[~,ixM] = max(lowestPnts(:,2));
fixM = ff(ixM);
P0 = X(ff(ixM),:);
% m = max(X(:,1));
% lowestPts = X(X(:,1)==m,:);
% [~,ixM] = max(lowestPts(:,2));
% P0 = lowestPts(ixM,:);

% Determine the second point in the radially sorted set, and where to start
% looping from
if fixM == 1
    next = 2; % 2nd point
    start = 3; % where, therefore, to start looping
elseif fixM == 2
    next =1 ;
    start = 3;
else
    next = 1;
    start = 2;
end
% sorted_order(i) gives the radial order of the ith point of X
% Put the first 2 points in sorted_order.
sorted_order = zeros(1,nbpoints);
sorted_order(1)=fixM;
sorted_order(2)= next;
B = 2; % as far as we sorted so far

% Sort radially
for i=start:nbpoints   
    if i==fixM
        continue
    end
    P2 = X(i,:);
    k=2;
    P1 = X(sorted_order(k),:);
    il = isLeft(P0,P1,P2,nr,nc);
    while (il > 0 && sorted_order(k+1)~=0)
        % pick the next point already sorted
        k=k+1;
        P1 = X(sorted_order(k),:);
        il = isLeft(P0,P1,P2,nr,nc);
    end
    if il < 0
        % must shift things to the right to make room for the new point
        sorted_order(k+1:B+1) = sorted_order(k:B);
        sorted_order(k) = i; 
    elseif il == 0
        d2P0 = [norm(P0-P1), norm(P0-P2)];
        [~,md]=max(d2P0);
        if md==2
            sorted_order(k)=i;
        end
    else
        % to the left of everything seen so far
        sorted_order(k+1) = i;
    end
    B = B+1;                
end
% the cases where il=0 throw out some points so there may be 0 entries in
% sorted_order. Here we get rid of them.
sorted_order = sorted_order(sorted_order~=0);
nchpnts = length(sorted_order);

% Get convex hull
stack = -ones(nchpnts,2); % pre-allocate for speed
stack(1:2,:) = X(sorted_order(1:2),:);
s = 2;
for k=3:nchpnts
%     s = size(stack,1);
    Pk = X(sorted_order(k),:);
    il = isLeft(X(sorted_order(s-1),:),X(sorted_order(s),:),Pk,nr,nc);
    while il <= 0 && size(stack,1) > 1
        % pop 
        stack(end,:) = [-1 -1]; s = s-1;
        il = isLeft(X(sorted_order(s-1),:),X(sorted_order(s),:),Pk,nr,nc);
    end
    stack(s+1,:) = Pk; s = s+1;
end

hull = stack(1:s,:);
area = polyarea(hull(:,1),hull(:,2));    
end

