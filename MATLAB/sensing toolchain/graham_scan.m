function hull = graham_scan(X)
% X is n-by-2 set of points in pixel coordinates
% hull is the convex hull of X
nbpoints = size(X,1);
% turn to x-y coordinates for sanity
X = [X(:,2),X(:,1)];
% find the lowest, rightmost point
m = min(X(:,2));
lowestPts = X(X(:,2)==m,:);
[~,ixM] = max(lowestPts(:,1));
P0 = lowestPts(ixM,:);

% Determine the second point in the radially sorted set, and where to start
% looping from
if ixM == 1
    next = 2; % 2nd point
    start = 3; % where, therefore, to start looping
elseif ixM == 2
    next =1 ;
    start = 3;
else
    next = 1;
    start = 2;
end
% sorted_order(i) gives the radial order of the ith point of X
% Put the first 2 points in sorted_order.
sorted_order = zeros(1,nbpoints);
sorted_order(1)=ixM;
sorted_order(2)= next;
B = 2; % as far as we sorted so far

% Sort radially
for i=start:nbpoints    
    P2 = X(i,:);
    k=2;
    P1 = X(sorted_order(k),:);
    il = isLeft(P0,P1,P2);
    while (il > 0 && sorted_order(k+1)~=0)
        k=k+1;
        P1 = X(sorted_order(k),:);
        il = isLeft(P0,P1,P2);
    end
    if il <= 0
        % must shift things to the right to make room for the new point
        sorted_order(k+1:B+1) = sorted_order(k:B);
        sorted_order(k) = i; 
    else
        % to the left of everything seen so far
        sorted_order(k+1) = i;
    end
    B = B+1;                
end

% Get convex hull

