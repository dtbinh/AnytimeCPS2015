function d = isLeft(P0, P1, P2, nr, nc )
% // isLeft(): test if a point is Left|On|Right of an infinite 2D line.
% //    Input:  three points P0, P1, and P2
% //    Return: >0 for P2 left of the line through P0 to P1
% //          =0 for P2 on the line
% //          <0 for P2 right of the line
% inline int
% isLeft( Point P0, Point P1, Point P2 )
% {
%     return ( (P1.x - P0.x) * (P2.y - P0.y)
%            - (P2.x - P0.x) * (P1.y - P0.y) );
% }
x0 = P0(2) - 1; y0 = nr - P0(1);
x1 = P1(2) - 1; y1 = nr - P1(1);
x2 = P2(2) - 1; y2 = nr - P2(1);

d = ( (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) );
 
